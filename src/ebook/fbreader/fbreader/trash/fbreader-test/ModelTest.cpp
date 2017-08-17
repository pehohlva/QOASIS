#include <iostream>

#include <ZLEncodingConverter.h>
#include <XMLOptions.h>
#include <unix/ZLUnixFSManager.h>

#include "../../src/model/Paragraph.h"
#include "../../src/bookmodel/BookModel.h"
#include "../../src/bookmodel/BookReader.h"

#include "../../src/collection/BookCollection.h"
#include "../../src/fbreader/CollectionView.h"
#include "../../src/fbreader/FBFileHandler.h"

const std::string BookCollection::DefaultBookPath = "~/FBooks:~/Books";

void dumpParagraph(const Paragraph &paragraph) {
	std::cout << "PARAGRAPH: ";
	for (Paragraph::Iterator it(paragraph); !it.isEnd(); it.next()) {
		ParagraphEntry::Kind kind = it.entryKind();
		std::cout << kind << " ";
		shared_ptr<ParagraphEntry> entry = it.entry();
		if (entry.isNull()) {
			std::cout << "NULL";
		} else {
			switch (kind) {
				case ParagraphEntry::TEXT_ENTRY:
					{
						TextEntry &text = (TextEntry&)*entry;
						std::string s;
						s.append(text.data(), text.dataLength());
						std::cout << s;
					}
					break;
				case ParagraphEntry::IMAGE_ENTRY:
					break;
				case ParagraphEntry::CONTROL_ENTRY:
				case ParagraphEntry::HYPERLINK_CONTROL_ENTRY:
					{
						ControlEntry &control = (ControlEntry&)*entry;
						std::cout << "CTRL" << control.kind();
						std::cout << (control.isStart() ? "+" : "-");
						std::cout << (control.isHyperlink() ? "+" : "-");
					}
					break;
				case ParagraphEntry::FORCED_CONTROL_ENTRY:
					break;
			}
		}
		std::cout << ";";
	}
	std::cout << "\n";
}

void dumpModel(const TextModel &model) {
	const int N = model.paragraphsNumber();
	for (int i = 0; i < N; ++i) {
		dumpParagraph(*model[i]);
	}
}

void dumpModel(const BookModel &model) {
	std::cout << "Book text:\n";
	dumpModel(model.bookTextModel());
	std::cout << "Contents table:\n";
	dumpModel(model.contentsModel());
	// TODO: dump all footnotes models
}

int main(int argc, const char **argv) {
	if (argc != 2) {
		std::cerr << "usage:\n	" << argv[0] << " <book file name>\n";
		return 1;
	}

	ZLUnixFSManager::createInstance();
	ZLEncodingConverter::setEncodingDescriptionPath(Files::PathPrefix + "encodings");
	XMLOptions::createInstance("FBReader");

	BookDescriptionPtr description = BookDescription::create(argv[1]);
	if (description.isNull()) {
		std::cerr << "couldn't read file " << argv[1] << "\n";
		return 1;
	}

	dumpModel(BookModel(description));

	return 0;
}
