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


	<!-- Apply Borders -->
	<xsl:template name="apply-border">	
		<xsl:param name="draw-style"/>		
						
		<xsl:variable name="border" select="$draw-style/@fo:border"/>		
		<xsl:variable name="border-value">
			<xsl:choose>
				<xsl:when test="$border = 'none'">0</xsl:when>
				<xsl:when test="$border"><xsl:value-of select='substring-before($border, "cm")' /></xsl:when>
				<xsl:otherwise>0</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="border-left" select="$draw-style/@fo:border-left" />
		<xsl:variable name="border-left-value">
			<xsl:choose>
				<xsl:when test="$border-left = 'none'">0</xsl:when>
				<xsl:when test="$border-left"><xsl:value-of select='substring-before($border-left, "cm")' /></xsl:when>
				<xsl:otherwise>0</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>		
				
		<xsl:variable name="border-right" select="$draw-style/@fo:border-right" />
		<xsl:variable name="border-right-value">
			<xsl:choose>
				<xsl:when test="$border-right = 'none'">0</xsl:when>
				<xsl:when test="$border-right"><xsl:value-of select='substring-before($border-right, "cm")' /></xsl:when>
				<xsl:otherwise>0</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>		

		<xsl:variable name="border-top" select="$draw-style/@fo:border-top" />
		<xsl:variable name="border-top-value">
			<xsl:choose>
				<xsl:when test="$border-top = 'none'">0</xsl:when>
				<xsl:when test="$border-top"><xsl:value-of select='substring-before($border-top, "cm")' /></xsl:when>
				<xsl:otherwise>0</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>		

		<xsl:variable name="border-bottom" select="$draw-style/@fo:border-bottom" />
		<xsl:variable name="border-bottom-value">
			<xsl:choose>
				<xsl:when test="$border-bottom = 'none'">0</xsl:when>
				<xsl:when test="$border-bottom"><xsl:value-of select='substring-before($border-bottom, "cm")' /></xsl:when>
				<xsl:otherwise>0</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>				
						
		<xsl:if test="$border">
			<xsl:attribute name="border-bottom-style">solid</xsl:attribute>
			<xsl:attribute name="border-top-style">solid</xsl:attribute>
			<xsl:attribute name="border-left-style">solid</xsl:attribute>
			<xsl:attribute name="border-right-style">solid</xsl:attribute>
			<xsl:variable name="border-colour" select='substring-after($border, "#")' />
			<xsl:attribute name="border-top-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-bottom-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-left-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-right-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-left-width"><xsl:value-of select="$border-value" />cm</xsl:attribute>
			<xsl:attribute name="border-right-width"><xsl:value-of select="$border-value" />cm</xsl:attribute>
			<xsl:attribute name="border-top-width"><xsl:value-of select="$border-value" />cm</xsl:attribute>
			<xsl:attribute name="border-bottom-width"><xsl:value-of select="$border-value" />cm</xsl:attribute>
		</xsl:if>

		<xsl:if test="$border-top">
			<xsl:attribute name="border-top-style">solid</xsl:attribute>
			<xsl:variable name="border-colour" select='substring-after($border-top, "#")' />
			<xsl:attribute name="border-top-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-top-width"><xsl:value-of select="$border-top-value" />cm</xsl:attribute>
		</xsl:if>
				
		<xsl:if test="$border-bottom">
			<xsl:attribute name="border-bottom-style">solid</xsl:attribute>
			<xsl:variable name="border-colour" select='substring-after($border-bottom, "#")' />
			<xsl:attribute name="border-bottom-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-bottom-width"><xsl:value-of select="$border-bottom-value" />cm</xsl:attribute>
		</xsl:if>
				
		<xsl:if test="$border-left">
			<xsl:attribute name="border-left-style">solid</xsl:attribute>
			<xsl:variable name="border-colour" select='substring-after($border-left, "#")' />
			<xsl:attribute name="border-left-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-left-width"><xsl:value-of select="$border-left-value" />cm</xsl:attribute>
		</xsl:if>
		
		<xsl:if test="$border-right">
			<xsl:attribute name="border-right-style">solid</xsl:attribute>
			<xsl:variable name="border-colour" select='substring-after($border-right, "#")' />
			<xsl:attribute name="border-right-color"><xsl:value-of select="concat('#', $border-colour)" /></xsl:attribute>
			<xsl:attribute name="border-right-width"><xsl:value-of select="$border-right-value" />cm</xsl:attribute>
		</xsl:if>
		
		<!-- border style -->
		<xsl:if test="$draw-style/@draw:stroke='solid'">
			<xsl:attribute name="border-bottom-style">solid</xsl:attribute>
			<xsl:attribute name="border-top-style">solid</xsl:attribute>
			<xsl:attribute name="border-left-style">solid</xsl:attribute>
			<xsl:attribute name="border-right-style">solid</xsl:attribute>
		</xsl:if>

		<xsl:if test="$draw-style/@svg:stroke-width">
			<xsl:variable name="stroke-width" select="$draw-style/@svg:stroke-width" />
			<xsl:attribute name="border-left-width"><xsl:value-of select="$stroke-width" /></xsl:attribute>
			<xsl:attribute name="border-right-width"><xsl:value-of select="$stroke-width" /></xsl:attribute>
			<xsl:attribute name="border-top-width"><xsl:value-of select="$stroke-width" /> </xsl:attribute>
			<xsl:attribute name="border-bottom-width"><xsl:value-of select="$stroke-width" /></xsl:attribute>
		</xsl:if>

		<xsl:if test="$draw-style/@svg:stroke-color">
			<xsl:variable name="stroke-color" select="$draw-style/@svg:stroke-color" />
			<xsl:attribute name="border-left-color"><xsl:value-of select="$stroke-color" /></xsl:attribute>
			<xsl:attribute name="border-right-color"><xsl:value-of select="$stroke-color" /></xsl:attribute>
			<xsl:attribute name="border-top-color"><xsl:value-of select="$stroke-color" /></xsl:attribute>
			<xsl:attribute name="border-bottom-color"><xsl:value-of select="$stroke-color" /></xsl:attribute>
		</xsl:if>

	</xsl:template>

</xsl:stylesheet>