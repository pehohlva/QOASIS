<?xml version="1.0" encoding="UTF-8"?>

<!--
	===========================================
	Office2fO
	===========================================
	
	Project Info:  http://www.openedgesoft.com/office2fo
	(C) Copyright 2008, OpenEdge www.openedgesoft.com
	
	This file is part of Office2fO
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
	
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.
	
	You should have received a copy of the GNU General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301, USA
	 
	copyright 2008 OpenEdge.
	license   http://www.gnu.org/licenses/gpl.txt GNU General Public License v2
	link      http://www.openedgesoft.com/office2fo Office2fO
	link      http://www.openedgesoft.com OpenEdge
-->
 
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:office="urn:oasis:names:tc:opendocument:xmlns:office:1.0"
	xmlns:style="urn:oasis:names:tc:opendocument:xmlns:style:1.0"
	xmlns:text="urn:oasis:names:tc:opendocument:xmlns:text:1.0"
	xmlns:table="urn:oasis:names:tc:opendocument:xmlns:table:1.0"
	xmlns:draw="urn:oasis:names:tc:opendocument:xmlns:drawing:1.0"
	xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0"
	xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns:dc="http://purl.org/dc/elements/1.1/"
	xmlns:meta="urn:oasis:names:tc:opendocument:xmlns:meta:1.0"
	xmlns:number="urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0"
	xmlns:svg="urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0"
	xmlns:chart="urn:oasis:names:tc:opendocument:xmlns:chart:1.0"
	xmlns:dr3d="urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0"
	xmlns:math="http://www.w3.org/1998/Math/MathML"
	xmlns:form="urn:oasis:names:tc:opendocument:xmlns:form:1.0"
	xmlns:script="urn:oasis:names:tc:opendocument:xmlns:script:1.0"
	xmlns:config="urn:oasis:names:tc:opendocument:xmlns:config:1.0"
	xmlns:ooo="http://openoffice.org/2004/office"
	xmlns:ooow="http://openoffice.org/2004/writer"
	xmlns:oooc="http://openoffice.org/2004/calc"
	xmlns:dom="http://www.w3.org/2001/xml-events"
	xmlns:xforms="http://www.w3.org/2002/xforms"
	xmlns:xsd="http://www.w3.org/2001/XMLSchema"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"	
	xmlns="http://www.w3.org/1999/xhtml">

	
	<xsl:template name="create-image">
		<xsl:param name="parent-style"/>
		<xsl:param name="width"/>
		<xsl:param name="height"/>
		<xsl:param name="left"/>
		<xsl:param name="top"/>		

		<xsl:variable name="vertical-pos" select="$parent-style/@style:vertical-pos" />
		<xsl:variable name="padding" select="$parent-style/@fo:padding" />
		<xsl:variable name="padding-left" select="$parent-style/@fo:padding-left" />
		<xsl:variable name="padding-right" select="$parent-style/@fo:padding-right" />
		<xsl:variable name="padding-top" select="$parent-style/@fo:padding-top" />
		<xsl:variable name="padding-bottom" select="$parent-style/@fo:padding-bottom" />		
		
		<fo:external-graphic xmlns:fo="http://www.w3.org/1999/XSL/Format">
		
		<xsl:choose>
			<xsl:when test="$vertical-pos='middle'">
				<xsl:attribute name="alignment-baseline">after-edge</xsl:attribute>
			</xsl:when>
			<xsl:when test="$vertical-pos='bottom'">
				<xsl:attribute name="baseline-shift">sub</xsl:attribute>
			</xsl:when>
		</xsl:choose>		
																			
		<xsl:if test="$width">
			<xsl:attribute name="content-width"><xsl:value-of select="$width"/></xsl:attribute>
		</xsl:if>
		
		<xsl:if test="$height">
		<xsl:attribute name="content-height"><xsl:value-of select="$height"/></xsl:attribute>
		</xsl:if>
							
		<xsl:if test="$left">
			<xsl:attribute name="left"><xsl:value-of select="$left"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="$top">
			<xsl:attribute name="top"><xsl:value-of select="$top"/></xsl:attribute>
		</xsl:if>
							
		<xsl:if test="$padding">
			<xsl:attribute name="padding"><xsl:value-of select="$padding" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="$padding-top">
			<xsl:attribute name="padding-top"><xsl:value-of select="$padding-top" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="$padding-bottom">
			<xsl:attribute name="padding-bottom"><xsl:value-of select="$padding-bottom" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="$padding-left">
			<xsl:attribute name="padding-left"><xsl:value-of select="$padding-left" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="$padding-right">
			<xsl:attribute name="padding-right"><xsl:value-of select="$padding-right" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="@xlink:href">
			<xsl:attribute name="src"><xsl:value-of select="concat('url(', ./@xlink:href, ')')" /></xsl:attribute>
		</xsl:if>
		<xsl:if test="office:binary-data">
			<xsl:if test="@svg:width">
				<xsl:attribute name="content-width"><xsl:value-of select="substring-before(./@svg:width - $padding, 'cm')" />cm</xsl:attribute>
			</xsl:if>
			<xsl:if test="@svg:height">
				<xsl:attribute name="content-height"><xsl:value-of select="substring-before(./@svg:height - $padding, 'cm')" />cm</xsl:attribute>
			</xsl:if>
			<xsl:attribute name="src">url('data:image;base64,<xsl:value-of select="office:binary-data" />')</xsl:attribute>
		</xsl:if>
		
		<xsl:call-template name="apply-border">
			<xsl:with-param name="draw-style" select="$parent-style"/>
		</xsl:call-template>
		
		</fo:external-graphic>
		
	</xsl:template>
	
</xsl:stylesheet>