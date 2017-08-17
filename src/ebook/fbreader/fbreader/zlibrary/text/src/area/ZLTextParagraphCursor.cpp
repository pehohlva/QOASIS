/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 * Copyright (C) 2016 Slava Monich <slava.monich@jolla.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <algorithm>

#include <ZLTextParagraph.h>
#include <ZLTextModel.h>

#include "ZLTextParagraphCursor.h"
#include "ZLTextWord.h"
#include "ZLTextParagraphBuilder.h"

ZLTextElementVector::~ZLTextElementVector() {
	for (ZLTextElementVector::const_iterator it = begin(); it != end(); ++it) {
		switch ((*it)->kind()) {
			case ZLTextElement::WORD_ELEMENT:
				myTextElementPool->storeWord((ZLTextWord*)*it);
				break;
			case ZLTextElement::CONTROL_ELEMENT:
				myTextElementPool->storeControlElement((ZLTextControlElement*)*it);
				break;
			case ZLTextElement::IMAGE_ELEMENT:
			case ZLTextElement::FORCED_CONTROL_ELEMENT:
			case ZLTextElement::FIXED_HSPACE_ELEMENT:
				delete *it;
				break;
			case ZLTextElement::INDENT_ELEMENT:
			case ZLTextElement::HSPACE_ELEMENT:
			case ZLTextElement::NB_HSPACE_ELEMENT:
			case ZLTextElement::BEFORE_PARAGRAPH_ELEMENT:
			case ZLTextElement::AFTER_PARAGRAPH_ELEMENT:
			case ZLTextElement::EMPTY_LINE_ELEMENT:
			case ZLTextElement::LINE_BREAK_ELEMENT:
			case ZLTextElement::START_REVERSED_SEQUENCE_ELEMENT:
			case ZLTextElement::END_REVERSED_SEQUENCE_ELEMENT:
			case ZLTextElement::EMPTY_ELEMENT:
				break;
		}
	}
}

ZLTextElementPool::ZLTextElementPool() {
	HSpaceElement = new ZLTextSpecialElement(ZLTextElement::HSPACE_ELEMENT);
	NBHSpaceElement = new ZLTextSpecialElement(ZLTextElement::NB_HSPACE_ELEMENT);
	BeforeParagraphElement = new ZLTextSpecialElement(ZLTextElement::BEFORE_PARAGRAPH_ELEMENT);
	AfterParagraphElement = new ZLTextSpecialElement(ZLTextElement::AFTER_PARAGRAPH_ELEMENT);
	EmptyLineElement = new ZLTextSpecialElement(ZLTextElement::EMPTY_LINE_ELEMENT);
	LineBreakElement = new ZLTextSpecialElement(ZLTextElement::LINE_BREAK_ELEMENT);
	StartReversedSequenceElement = new ZLTextSpecialElement(ZLTextElement::START_REVERSED_SEQUENCE_ELEMENT);
	EndReversedSequenceElement = new ZLTextSpecialElement(ZLTextElement::END_REVERSED_SEQUENCE_ELEMENT);
	EmptyElement = new ZLTextSpecialElement(ZLTextElement::EMPTY_ELEMENT);
}

ZLTextElementPool::~ZLTextElementPool() {
	delete HSpaceElement;
	delete NBHSpaceElement;
	delete BeforeParagraphElement;
	delete AfterParagraphElement;
	delete EmptyLineElement;
	delete LineBreakElement;
	delete StartReversedSequenceElement;
	delete EndReversedSequenceElement;
	delete EmptyElement;
}

ZLTextParagraphCursorPtr ZLTextParagraphCursorCache::cursor(const ZLTextModel &model, size_t index) {
	const ZLTextParagraph *paragraph = model[index];
	ZLTextParagraphCursorPtr result = ourCache[paragraph];
	if (result.isNull()) {
		if (model.kind() == ZLTextModel::TREE_MODEL) {
			result = new ZLTextTreeParagraphCursor((const ZLTextTreeModel&)model, index, this);
		} else {
			result = new ZLTextPlainParagraphCursor(model, index, this);
		}
		ourCache[paragraph] = result;
	}
	return result;
}

ZLTextPlainParagraphCursor::ZLTextPlainParagraphCursor(const ZLTextModel &model, size_t index, ZLTextParagraphCursorCache *cache) : ZLTextParagraphCursor(model, index, cache) {
}

ZLTextTreeParagraphCursor::ZLTextTreeParagraphCursor(const ZLTextTreeModel &model, size_t index, ZLTextParagraphCursorCache *cache) : ZLTextParagraphCursor(model, index, cache) {
}

ZLTextParagraphCursor::ZLTextParagraphCursor(const ZLTextModel &model, size_t index, ZLTextParagraphCursorCache *cache) : myModel(model), myElements(cache->elementPool()), myParagraphCursorCache(cache) {
	myIndex = std::min(index, myModel.paragraphsNumber() - 1);
	fill();
}

ZLTextParagraphCursor::~ZLTextParagraphCursor() {
}

ZLTextParagraphCursorPtr ZLTextPlainParagraphCursor::previous() const {
	return isFirst() ? 0 : myParagraphCursorCache->cursor(myModel, myIndex - 1);
}

ZLTextParagraphCursorPtr ZLTextTreeParagraphCursor::previous() const {
	if (isFirst()) {
		return 0;
	}
	const ZLTextTreeParagraph *oldTreeParagraph = (const ZLTextTreeParagraph*)myModel[myIndex];
	const ZLTextTreeParagraph *parent = oldTreeParagraph->parent();
	size_t index = myIndex - 1;
	const ZLTextTreeParagraph *newTreeParagraph = (ZLTextTreeParagraph*)myModel[index];
	if (newTreeParagraph != parent) {
		const ZLTextTreeParagraph *lastNotOpen = newTreeParagraph;
		for (const ZLTextTreeParagraph *p = newTreeParagraph->parent(); p != parent; p = p->parent()) {
			if (!p->isOpen()) {
				lastNotOpen = p;
			}
		}
		while (myModel[index] != lastNotOpen) {
			--index;
		}
	}
	return myParagraphCursorCache->cursor(myModel, index);
}

ZLTextParagraphCursorPtr ZLTextPlainParagraphCursor::next() const {
	return isLast() ? 0 : myParagraphCursorCache->cursor(myModel, myIndex + 1);
}

ZLTextParagraphCursorPtr ZLTextTreeParagraphCursor::next() const {
	if (myIndex + 1 == myModel.paragraphsNumber()) {
		return 0;
	}
	const ZLTextTreeParagraph *current = (const ZLTextTreeParagraph*)myModel[myIndex];
	if (!current->children().empty() && current->isOpen()) {
		return myParagraphCursorCache->cursor(myModel, myIndex + 1);
	}

	const ZLTextTreeParagraph *parent = current->parent();
	while ((parent != 0) && (current == parent->children().back())) {
		current = parent;
		parent = current->parent();
	}
	if (parent != 0) {
		size_t index = myIndex + 1;
		while (((const ZLTextTreeParagraph*)myModel[index])->parent() != parent) {
			++index;
		}
		return myParagraphCursorCache->cursor(myModel, index);
	}
	return 0;
}

bool ZLTextParagraphCursor::isFirst() const {
	return
		(myIndex == 0) ||
		(myModel[myIndex]->kind() == ZLTextParagraph::END_OF_TEXT_PARAGRAPH) ||
		(myModel[myIndex - 1]->kind() == ZLTextParagraph::END_OF_TEXT_PARAGRAPH);
}

bool ZLTextPlainParagraphCursor::isLast() const {
	return
		(myIndex + 1 == myModel.paragraphsNumber()) ||
		(myModel[myIndex + 1]->kind() == ZLTextParagraph::END_OF_TEXT_PARAGRAPH);
}

bool ZLTextTreeParagraphCursor::isLast() const {
	if ((myIndex + 1 == myModel.paragraphsNumber()) ||
			(myModel[myIndex + 1]->kind() == ZLTextParagraph::END_OF_TEXT_PARAGRAPH)) {
		return true;
	}
	const ZLTextTreeParagraph *current = (const ZLTextTreeParagraph*)myModel[myIndex];
	if (current->isOpen() && !current->children().empty()) {
		return false;
	}
	const ZLTextTreeParagraph *parent = current->parent();
	while (parent != 0) {
		if (current != parent->children().back()) {
			return false;
		}
		current = parent;
		parent = current->parent();
	}
	return true;
}

const ZLTextParagraph &ZLTextParagraphCursor::paragraph() const {
	return *myModel[myIndex];
}

bool ZLTextParagraphCursor::isEndOfSection() const {
	return myModel[myIndex]->kind() == ZLTextParagraph::END_OF_SECTION_PARAGRAPH;
}

ZLTextMark ZLTextWordCursor::position() const {
	if (myParagraphCursor.isNull()) {
		return ZLTextMark();
	}
	const ZLTextParagraphCursor &paragraph = *myParagraphCursor;
	size_t paragraphLength = paragraph.paragraphLength();
	unsigned int elementIndex = myElementIndex;
	while ((elementIndex != paragraphLength) && (paragraph[elementIndex].kind() != ZLTextElement::WORD_ELEMENT)) {
		++elementIndex;
	}
	if (elementIndex != paragraphLength) {
		return ZLTextMark(paragraph.index(), ((ZLTextWord&)paragraph[elementIndex]).ParagraphOffset, 0);
	}
	return ZLTextMark(paragraph.index() + 1, 0, 0);
}

void ZLTextParagraphCursor::processControlParagraph(const ZLTextParagraph &paragraph) {
	for (ZLTextParagraph::Iterator it = paragraph; !it.isEnd(); it.next()) {
		myElements.push_back(elementPool()->getControlElement(it.entry()));
	}
}

void ZLTextParagraphCursor::fill() {
	const ZLTextParagraph &paragraph = *myModel[myIndex];
	switch (paragraph.kind()) {
		case ZLTextParagraph::TEXT_PARAGRAPH:
		case ZLTextParagraph::TREE_PARAGRAPH:
		{
			Builder builder(*this);
			builder.fill();
			break;
		}
		case ZLTextParagraph::EMPTY_LINE_PARAGRAPH:
			processControlParagraph(paragraph);
			myElements.push_back(elementPool()->EmptyLineElement);
			break;
		case ZLTextParagraph::BEFORE_SKIP_PARAGRAPH:
			processControlParagraph(paragraph);
			myElements.push_back(elementPool()->BeforeParagraphElement);
			break;
		case ZLTextParagraph::AFTER_SKIP_PARAGRAPH:
			processControlParagraph(paragraph);
			myElements.push_back(elementPool()->AfterParagraphElement);
			break;
		case ZLTextParagraph::END_OF_SECTION_PARAGRAPH:
		case ZLTextParagraph::END_OF_TEXT_PARAGRAPH:
			break;
	}
}

void ZLTextParagraphCursor::clear() {
	myElements.clear();
}

void ZLTextParagraphCursorCache::clear() {
	ourCache.clear();
}

void ZLTextParagraphCursorCache::cleanup() {
	std::map<const ZLTextParagraph*, weak_ptr<ZLTextParagraphCursor> > cleanedCache;
	for (std::map<const ZLTextParagraph*, weak_ptr<ZLTextParagraphCursor> >::iterator it = ourCache.begin(); it != ourCache.end(); ++it) {
		if (!it->second.isNull()) {
			cleanedCache.insert(*it);
		}
	}
	ourCache.swap(cleanedCache);
}

void ZLTextWordCursor::rebuild() {
	if (!isNull()) {
		myParagraphCursor->clear();
		myParagraphCursor->fill();
	}
}

void ZLTextWordCursor::setCharIndex(int charIndex) {
	charIndex = std::max(charIndex, 0);
	myCharIndex = 0;
	if (charIndex > 0) {
		const ZLTextElement &element = (*myParagraphCursor)[myElementIndex];
		if (element.kind() == ZLTextElement::WORD_ELEMENT) {
			if (charIndex <= (int)((const ZLTextWord&)element).Length) {
				myCharIndex = charIndex;
			}
		}
	}
}

void ZLTextWordCursor::moveTo(int elementIndex, int charIndex) {
	if (!isNull()) {
		if ((elementIndex == 0) && (charIndex == 0)) {
			myElementIndex = 0;
			myCharIndex = 0;
		} else {
			elementIndex = std::max(0, elementIndex);
			size_t size = myParagraphCursor->paragraphLength();
			if ((size_t)elementIndex > size) {
				myElementIndex = size;
				myCharIndex = 0;
			} else {
				myElementIndex = elementIndex;
				setCharIndex(charIndex);
			}
		}
	}
}

const ZLTextWordCursor &ZLTextWordCursor::operator = (ZLTextParagraphCursorPtr paragraphCursor) {
	myElementIndex = 0;
	myCharIndex = 0;
	myParagraphCursor = paragraphCursor;
	moveToParagraphStart();
	return *this;
}

void ZLTextWordCursor::moveToParagraph(int paragraphIndex) {
	if (!isNull() && (paragraphIndex != (int)myParagraphCursor->index())) {
		myParagraphCursor = myParagraphCursor->cursor(paragraphIndex);
		moveToParagraphStart();
	}
}

bool ZLTextWordCursor::nextParagraph() {
	if (!isNull()) {
		if (!myParagraphCursor->isLast()) {
			myParagraphCursor = myParagraphCursor->next();
			moveToParagraphStart();
			return true;
		}
	}
	return false;
}

bool ZLTextWordCursor::previousParagraph() {
	if (!isNull()) {
		if (!myParagraphCursor->isFirst()) {
			myParagraphCursor = myParagraphCursor->previous();
			moveToParagraphStart();
			return true;
		}
	}
	return false;
}

void ZLTextWordCursor::moveToParagraphStart() {
	if (!isNull()) {
		myElementIndex = 0;
		myCharIndex = 0;
	}
}

void ZLTextWordCursor::moveToParagraphEnd() {
	if (!isNull()) {
		myElementIndex = myParagraphCursor->paragraphLength();
		myCharIndex = 0;
	}
}

bool ZLTextWordCursor::operator < (const ZLTextWordCursor &cursor) const {
	int pn0 = myParagraphCursor->index();
	int pn1 = cursor.myParagraphCursor->index();
	if (pn0 < pn1) return true;
	if (pn1 < pn0) return false;
	if (myElementIndex < cursor.myElementIndex) return true;
	if (myElementIndex > cursor.myElementIndex) return false;
	return myCharIndex < cursor.myCharIndex;
}
