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

	<xsl:include href="padding.xsl" />
	<xsl:include href="images.xsl" />
	<xsl:include href="borders.xsl" />

	<xsl:output method="xml" encoding="UTF-8"
		media-type="application/xhtml+xml" indent="yes"
		omit-xml-declaration="yes" />

	<!-- global variables -->
	<xsl:variable name="random-nodes" select="document('')//node()" />	

	<xsl:variable name="page-master-properties"
		select="/office:document/office:automatic-styles/style:page-layout/style:page-layout-properties" />

	<xsl:variable name="page-width"
		select="$page-master-properties/@fo:page-width" />
	<xsl:variable name="page-height"
		select="$page-master-properties/@fo:page-height" />		
		
	<xsl:variable name="page-margin-top"
		select="$page-master-properties/@fo:margin-top" />
	<xsl:variable name="page-margin-bottom"
		select="$page-master-properties/@fo:margin-bottom" />
	<xsl:variable name="page-margin-left"
		select="$page-master-properties/@fo:margin-left" />
	<xsl:variable name="page-margin-right"
		select="$page-master-properties/@fo:margin-right" />

	<!-- default styles -->
	<xsl:variable name="default-style-paragraph"
		select="/office:document/office:styles/style:default-style[@style:family='paragraph']" />

	<xsl:variable name="default-style-table-row" 
		select="/office:document/office:styles/style:default-style[@style:family='table-row']" />
		
	<xsl:variable name="all-auto-styles" 
		select="/office:document/office:styles" />		
			
	<!-- Root -->
	<xsl:template match="/">
	
		<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:layout-master-set xmlns:fo="http://www.w3.org/1999/XSL/Format">
				<xsl:call-template name="pageTemplate">				
					<xsl:with-param name="pagename">mainpage</xsl:with-param>
					<xsl:with-param name="regionname">main</xsl:with-param>
				</xsl:call-template>
				<xsl:call-template name="pageTemplate">				
					<xsl:with-param name="pagename">firstpage</xsl:with-param>
					<xsl:with-param name="regionname">first</xsl:with-param>
				</xsl:call-template>
				<xsl:call-template name="pageTemplate">				
					<xsl:with-param name="pagename">lastpage</xsl:with-param>
					<xsl:with-param name="regionname">last</xsl:with-param>
				</xsl:call-template>
				<fo:page-sequence-master master-name="main-sequence" xmlns:fo="http://www.w3.org/1999/XSL/Format">
					<fo:repeatable-page-master-alternatives>
						<fo:conditional-page-master-reference master-reference="firstpage-layout" page-position="first"/>
						<fo:conditional-page-master-reference master-reference="lastpage-layout" page-position="last"/>
						<fo:conditional-page-master-reference master-reference="mainpage-layout" page-position="rest"/>
					</fo:repeatable-page-master-alternatives>
				</fo:page-sequence-master>
			</fo:layout-master-set>

			<fo:page-sequence master-reference="main-sequence" xmlns:fo="http://www.w3.org/1999/XSL/Format">
				<fo:title xmlns:fo="http://www.w3.org/1999/XSL/Format">Sample Document</fo:title>
				<fo:flow flow-name="frame-body">
					<xsl:apply-templates select="office:document/office:body/office:text/*"/>											
				</fo:flow>
			</fo:page-sequence>

		</fo:root>
	</xsl:template>
		
	<xsl:template match="office:forms">	
	</xsl:template>
	
	<xsl:template match="text:sequence-decls">		
	</xsl:template>
	
	<xsl:template match="office:script">
	</xsl:template>
		
	<xsl:template match="office:font-decls">
	</xsl:template>	
	
	<!-- Page template setup -->
	<xsl:template name="pageTemplate">	
		<xsl:param name="pagename" />		
		<xsl:param name="regionname" />
		<fo:simple-page-master xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<xsl:attribute name="margin-top"><xsl:value-of select="$page-margin-top" /></xsl:attribute>
			<xsl:attribute name="margin-bottom"><xsl:value-of select="$page-margin-bottom" /></xsl:attribute>
			<xsl:attribute name="margin-left"><xsl:value-of select="$page-margin-left" /></xsl:attribute>
			<xsl:attribute name="margin-right"><xsl:value-of select="$page-margin-right" /></xsl:attribute>
	
			<xsl:attribute name="page-width"><xsl:value-of select="$page-width" /></xsl:attribute>
			<xsl:attribute name="page-height"><xsl:value-of select="$page-height" /></xsl:attribute>
			<xsl:attribute name="master-name"><xsl:value-of select="$pagename" />-layout</xsl:attribute>
	
			<fo:region-body region-name="frame-body" margin-bottom="0mm" margin-top="0mm" margin-left="0mm" margin-right="0mm">
	
				<xsl:if test="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/office:binary-data">
					<xsl:attribute name="background-image">
						<xsl:if test="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/office:binary-data ">data:image;base64,<xsl:value-of select="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/office:binary-data" /></xsl:if>
					</xsl:attribute>				
					<xsl:attribute name="background-repeat">
						<xsl:value-of select="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/@style:repeat"/>
					</xsl:attribute>
	
					<xsl:choose>
						<xsl:when test="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/@style:position = 'top center'">
							<xsl:attribute name="background-position-horizontal">center</xsl:attribute>
							<xsl:attribute name="background-position-vertical">top</xsl:attribute>
						</xsl:when>
						<xsl:when test="office:document/office:automatic-styles/style:page-master/style:properties/style:background-image/@style:position = 'top left'">
							<xsl:attribute name="background-position-horizontal">left</xsl:attribute>
							<xsl:attribute name="background-position-vertical">top</xsl:attribute>
						</xsl:when>
					</xsl:choose>							
				</xsl:if>
			</fo:region-body>
			<fo:region-before extent="10mm">				
				<xsl:attribute name="region-name"><xsl:value-of select="$regionname" />-region</xsl:attribute>
			</fo:region-before>
		</fo:simple-page-master>
	
	</xsl:template>	
  <!-- -->

	<!-- Applies the styles -->
	<xsl:template name="applyStyle">		
		<xsl:param name="style-name"/>						
		
		<xsl:variable name="style" select="//style:style[@style:name=$style-name]"/>		
		
		<xsl:if test="$style/@style:parent-style-name">
			<xsl:call-template name="applyStyle">
				<xsl:with-param name="style-name" select="$style/@style:parent-style-name"/>
			</xsl:call-template>
		</xsl:if>
		
		<xsl:for-each select="$style/*">
			
			<!-- Convert some of the properties -->
			<xsl:if test="@style:font-name">
				<xsl:attribute name="font-family">
					<xsl:value-of select="@style:font-name"/>
				</xsl:attribute>
			</xsl:if>			
		
			<!-- Copy FO attributes -->
			<xsl:for-each select="@fo:*" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0">
				<xsl:attribute name="{local-name()}"><xsl:value-of select="." /></xsl:attribute>
			</xsl:for-each>
												
		</xsl:for-each>	
		
	</xsl:template>
	
	
	<!-- Header -->
	<xsl:template match="text:h">			
		<xsl:param name="parent-width"/>
		
		<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">

		<!-- Fix the line spacing -->
		<xsl:attribute name="line-height">1.17</xsl:attribute>			
			
			<xsl:if test="@text:style-name">
				<xsl:call-template name="applyStyle">
					<xsl:with-param name="style-name" select="@text:style-name"/>
				</xsl:call-template>
			</xsl:if>
			
			<xsl:apply-templates>				
				<xsl:with-param name="parent-width" select="$parent-width"/>
			</xsl:apply-templates>
						
		</fo:block>
	</xsl:template>
	
	<!-- Paragraph -->
	<xsl:template match="text:p">		
		<xsl:param name="parent-width" />
		<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
		
			<!-- Fix the line spacing -->
			<xsl:attribute name="line-height">1.17</xsl:attribute>
		
			<!-- Default paragraph style -->
			<xsl:if test="$default-style-paragraph/style:text-properties/@fo:font-size">
				<xsl:attribute name="font-size"><xsl:value-of select="$default-style-paragraph/style:text-properties/@fo:font-size" /></xsl:attribute>
			</xsl:if>

			<xsl:if test="$default-style-paragraph/style:text-properties/@fo:font-weight">
				<xsl:attribute name="font-size"><xsl:value-of select="$default-style-paragraph/style:text-properties/@fo:font-weight" /></xsl:attribute>
			</xsl:if>			
			
			<xsl:if test="$default-style-paragraph/style:text-properties/@fo:font-family">
				<xsl:attribute name="font-family"><xsl:value-of select="$default-style-paragraph/style:text-properties/@fo:font-family" /></xsl:attribute>
			</xsl:if>

			<xsl:if test="$default-style-paragraph/style:text-properties/@style:font-name">
					<xsl:variable name="font-name" select="$default-style-paragraph/style:text-properties/@style:font-name"/>					
					<xsl:attribute name="font-family"><xsl:value-of select="$font-name"/></xsl:attribute>				
			</xsl:if>
			
			<!-- apply styles -->
			<xsl:if test="@text:style-name">
				<xsl:call-template name="applyStyle">
					<xsl:with-param name="style-name" select="@text:style-name"/>
				</xsl:call-template>
			</xsl:if>			
			
			<xsl:choose>
				<xsl:when test="string-length(current()) = 0">
					<xsl:text> &#160;</xsl:text>
					<xsl:apply-templates>											
						<xsl:with-param name="parent-width" select="$parent-width"/>
					</xsl:apply-templates>
				</xsl:when>

				<xsl:otherwise>
					<xsl:apply-templates>						
						<xsl:with-param name="parent-width" select="$parent-width"/>
					</xsl:apply-templates>
				</xsl:otherwise>
			</xsl:choose>

		</fo:block>
	</xsl:template>

	<!-- Lists -->
	<xsl:template match="text:list">			
		
		<xsl:variable name="list-style-name" select="@text:style-name"/>					
		<xsl:variable name="list-style" select="//text:list-style[@style:name=$list-style-name]"/>
		
		<fo:list-block xmlns:fo="http://www.w3.org/1999/XSL/Format">												
			<xsl:apply-templates>				
				<xsl:with-param name="list-style" select="$list-style"/>
			</xsl:apply-templates>
		</fo:list-block>
		
	</xsl:template>

	<xsl:template match="text:list-header">		
		<xsl:param name="list-style"/>
		
		<fo:list-item xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:list-item-label end-indent="label-end()">
				<fo:block/>
			</fo:list-item-label>
			<fo:list-item-body start-indent="body-start()">
				<fo:block>
					<xsl:apply-templates/>
				</fo:block>
			</fo:list-item-body>	
		</fo:list-item>
	</xsl:template>
	
	<xsl:template match="text:list-item">			
		<xsl:param name="list-style"/>		
		
		<fo:list-item xmlns:fo="http://www.w3.org/1999/XSL/Format">
			
			<fo:list-item-label end-indent="label-end()">
				<fo:block>
					<xsl:value-of select="$list-style/text:list-level-style-bullet/@text:bullet-char"/>										
				</fo:block>
				
			</fo:list-item-label>
			
			<fo:list-item-body start-indent="body-start()">
				<fo:block>
					<xsl:apply-templates/>
				</fo:block>
			</fo:list-item-body>			
			
		</fo:list-item>
		
	</xsl:template>
	 
	<!-- Inline -->
	<xsl:template match="text:span">		
		<fo:inline xmlns:fo="http://www.w3.org/1999/XSL/Format">

			<!-- FO attributes -->
			<xsl:variable name="text-style-name" select="@text:style-name" />
			<xsl:variable name="text-style" select="//style:style[@style:name=$text-style-name]/style:text-properties" />

			<!-- text position attribute -->
			<xsl:if test="$text-style/@style:text-position">
				<xsl:variable name="text-position" select="$text-style/@style:text-position" />
				<xsl:variable name="baseline-shift" select='substring-before($text-position, " ")' />
				<xsl:variable name="font-size" select='substring-after($text-position, " ")' />

				<xsl:attribute name="baseline-shift"><xsl:value-of select="$baseline-shift" /></xsl:attribute>
				<xsl:attribute name="font-size"><xsl:value-of select="$font-size" /> </xsl:attribute>
			</xsl:if>

			<!-- Underline -->
			<xsl:if test="$text-style/@style:text-underline = 'single'">
				<xsl:attribute name="text-decoration">underline</xsl:attribute>
				
			</xsl:if>

			<!-- Line through -->
			<xsl:if test="$text-style/@style:text-crossing-out = 'single-line'">
				<xsl:attribute name="text-decoration">line-through</xsl:attribute>
			</xsl:if>

			<!-- Font Family -->
			<xsl:if test="$text-style/@style:font-name">
				<xsl:attribute name="font-family"><xsl:value-of select="$text-style/@style:font-name"/></xsl:attribute>
			</xsl:if>
			
			<!-- Copy FO attributes -->
			<xsl:call-template name="applyStyle">
				<xsl:with-param name="style-name" select="$text-style-name"/>
			</xsl:call-template>

			<xsl:value-of select="." />			
		</fo:inline>
	</xsl:template>
	
	<xsl:template match="table:table">	
			
		<!-- table style -->
		<xsl:variable name="table-style-name"
			select="@table:style-name" />
		<xsl:variable name="table-style"
			select="//style:style[@style:name=$table-style-name and @style:family='table']/style:table-properties" />

		<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<fo:table>
			
				<xsl:if test="@table:name">				
					<xsl:attribute name="id"><xsl:value-of select="@table:name" /></xsl:attribute>				
				</xsl:if>
			
				<xsl:if test="$table-style/@style:width">
					<xsl:attribute name="width"><xsl:value-of select="$table-style/@style:width" /></xsl:attribute>
				</xsl:if>
				
				<xsl:if test="$table-style/@fo:margin-top">
					<xsl:attribute name="margin-top"><xsl:value-of select="$table-style/@fo:margin-top" /></xsl:attribute>
				</xsl:if>
				
				<xsl:if test="$table-style/@fo:margin-bottom">
					<xsl:attribute name="margin-bottom"><xsl:value-of select="$table-style/@fo:margin-bottom" /></xsl:attribute>
				</xsl:if>
				
				<xsl:if test="$table-style/@fo:margin-left">
					<xsl:attribute name="margin-left"><xsl:value-of select="$table-style/@fo:margin-left" /></xsl:attribute>
				</xsl:if>
				
				<xsl:if test="$table-style/@fo:margin-right">
					<xsl:attribute name="margin-right"><xsl:value-of select="$table-style/@fo:margin-right" /></xsl:attribute>
				</xsl:if>

				<!-- build table columns -->
				<xsl:for-each select="table:table-column">

					<xsl:choose>
						<xsl:when test="@table:number-columns-repeated">
							<xsl:call-template name="iterateTableColumns">							
								<xsl:with-param name="numIterations" select="@table:number-columns-repeated" />
								<xsl:with-param name="column" select="." />								
							</xsl:call-template>
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="iterateTableColumns">							
								<xsl:with-param name="numIterations" select="'1'" />
								<xsl:with-param name="column" select="." />								
							</xsl:call-template>
						</xsl:otherwise>
					</xsl:choose>

				</xsl:for-each>				

				<!-- Table header rows -->
				<xsl:apply-templates select="table:table-header-rows"/>										

				<!-- Table body -->
				<fo:table-body>
					<xsl:apply-templates select="table:table-row"/>
				</fo:table-body>				
				
			</fo:table>
		</fo:block>

	</xsl:template>	
	
	<!-- Table column iterations -->
	<xsl:template name="iterateTableColumns">
		<xsl:param name="numIterations" />		
		<xsl:param name="column" />		

		<xsl:variable name="column-style-name" select="@table:style-name" />
		<xsl:variable name="column-style" select="//style:style[@style:name=$column-style-name]/style:table-column-properties" />

		<xsl:for-each select="$random-nodes[position() &lt;= $numIterations]">
			<fo:table-column xmlns:fo="http://www.w3.org/1999/XSL/Format">
				<xsl:attribute name="column-width">
                      <xsl:value-of select="$column-style/@style:column-width" />
				</xsl:attribute>
			</fo:table-column>
		</xsl:for-each>
	</xsl:template>	
	
	<!-- Table Headers -->
	<xsl:template match="table:table-header-rows">		
		<fo:table-header xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<xsl:apply-templates/>
		</fo:table-header>
	</xsl:template>
	
	<!-- Table Rows -->
	<xsl:template match="table:table-row">
				
		<xsl:variable name="row-style-name" select="@table:style-name"/>
		<xsl:variable name="row-style" select="//style:style[@style:name=$row-style-name]/style:properties" />
		
		<fo:table-row xmlns:fo="http://www.w3.org/1999/XSL/Format">
					
			<!-- apply default values -->
			<xsl:for-each select="$default-style-table-row/style:properties/@fo:*" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0">
				<xsl:attribute name="{local-name()}"><xsl:value-of select="."/></xsl:attribute>
			</xsl:for-each>
		
			<xsl:if test="$row-style/@style:row-height">
				<xsl:attribute name="height"><xsl:value-of select="$row-style/@style:row-height"/></xsl:attribute>								
			</xsl:if>
		
			<xsl:choose>
				<xsl:when test="$row-style/@style:row-height">
					<xsl:apply-templates select="table:table-cell">						
						<xsl:with-param name="cell-height" select="$row-style/@style:row-height"/>	
					</xsl:apply-templates>
				</xsl:when>
				<xsl:otherwise>
					<xsl:apply-templates select="table:table-cell"/>											
				</xsl:otherwise>
			</xsl:choose>
			
		</fo:table-row>
	</xsl:template>

	<!-- Table Cell -->
	<xsl:template match="table:table-cell">			
		<xsl:param name="cell-height"/>		
		
		<xsl:variable name="cell-style-name" select="@table:style-name" />
		<xsl:variable name="cell-style" select="//style:style[@style:name=$cell-style-name]/style:table-cell-properties" />

		<xsl:variable name="pos" select="position()" />
		<xsl:variable name="col-style1" select="../../table:table-column[position()=$pos]/@table:style-name" />
		<!--parent:<xsl:value-of select="$col-style"/>:parent-->
		<xsl:variable name="col-style" select="//style:style[@style:name=$col-style1]/style:table-column-properties" />
		<xsl:variable name="col-width" select="$col-style/@style:column-width" />
		<xsl:variable name="col-width-value" select='substring-before($col-width, "cm")' />
		
		<fo:table-cell xmlns:fo="http://www.w3.org/1999/XSL/Format">

			<!-- Copy the cell properties and change the sizes -->
			<xsl:call-template name="applyStyle">
				<xsl:with-param name="style-name" select="$cell-style-name"/>
			</xsl:call-template>
						
			<xsl:for-each select="$cell-style/@fo:*" xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0">

				<xsl:variable name="attrib-name" select="local-name()"/>
				
				<xsl:if test="starts-with($attrib-name, 'border')">
				
					<xsl:variable name="propB" select='substring-before(., "cm")' />
					<xsl:choose>
						<xsl:when test="$propB">
							<xsl:variable name="propA" select='substring-after(., "cm")' />
							<xsl:variable name="propBNew" select='number($propB) * number("1")' />
							<xsl:variable name="prop" select='concat($propBNew, "cm ", $propA)' />													
							<xsl:attribute name="{local-name()}"><xsl:value-of select="$prop" /></xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="{local-name()}"><xsl:value-of select="." /></xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
			
				</xsl:if>
				
			</xsl:for-each>
						
			<!-- background image -->
			<xsl:if test="$cell-style/style:background-image">
				<xsl:attribute name="background-image">
					<xsl:if test="$cell-style/style:background-image/@xlink:href">
						<xsl:value-of select="$cell-style/style:background-image/@xlink:href"/>
					</xsl:if>
					<xsl:if test="$cell-style/style:background-image/office:binary-data">data:image;base64,<xsl:value-of select="$cell-style/style:background-image/office:binary-data" /></xsl:if>
				</xsl:attribute>				
				<xsl:attribute name="background-repeat">
					<xsl:value-of select="$cell-style/style:background-image/@style:repeat"/>
				</xsl:attribute>				
			</xsl:if>

			<xsl:choose>
				<xsl:when test="$cell-height">
					<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format">
						<xsl:attribute name="height"><xsl:value-of select="$cell-height"/></xsl:attribute>
						<xsl:attribute name="overflow">hidden</xsl:attribute>						
						<xsl:apply-templates>													
							<xsl:with-param name="parent-width" select="$col-width-value" />							
						</xsl:apply-templates>
					</fo:block-container>
				</xsl:when>

				<xsl:otherwise>
					<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format">
						<xsl:apply-templates>							
							<xsl:with-param name="parent-width" select="$col-width-value" />
						</xsl:apply-templates>										
					</fo:block-container>
				</xsl:otherwise>			
			</xsl:choose>

		</fo:table-cell>		
	</xsl:template>
	
	<xsl:template match="draw:frame">
		<xsl:param name="parent-width"/>
		
		<xsl:variable name="style-name" select="@draw:style-name"/>
		<xsl:variable name="frame-style" select="//style:style[@style:name=$style-name]/style:graphic-properties"/>
		
		<xsl:choose>
			<xsl:when test="@text:anchor-type='page'">
			
				<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format">
					<xsl:attribute name="position">fixed</xsl:attribute >
					
					<xsl:call-template name="apply-current-position">
						<xsl:with-param name="component" select="."/>
					</xsl:call-template>
					
					<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
						<xsl:apply-templates>
							<xsl:with-param name="parent-style" select="$frame-style"/>							
							<xsl:with-param name="width" select="@svg:width"/>
							<xsl:with-param name="height" select="@svg:height"/>
							<xsl:with-param name="left" select="@svg:x"/>
							<xsl:with-param name="top" select="@svg:y"/>				
						</xsl:apply-templates>						
					</fo:block>
				</fo:block-container>
				
			</xsl:when>
				
			<xsl:otherwise>
							
				<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format">		
								
				<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
					<xsl:attribute name="position">relative</xsl:attribute>
					<xsl:call-template name="apply-current-position">
						<xsl:with-param name="component" select="."/>
					</xsl:call-template>
					
					<xsl:apply-templates>
						<xsl:with-param name="parent-style" select="$frame-style"/>
						<xsl:with-param name="width" select="@svg:width"/>
						<xsl:with-param name="height" select="@svg:height"/>						
						<xsl:with-param name="left" select="@svg:x"/>
						<xsl:with-param name="top" select="@svg:y"/>
					</xsl:apply-templates>											
					
				</fo:block>
				
			</fo:block-container>			
			
			</xsl:otherwise>
			
		</xsl:choose>
		
	</xsl:template>
	
	<xsl:template match="draw:image">
		<xsl:param name="parent-style"/>
		<xsl:param name="width"/>
		<xsl:param name="height"/>
		<xsl:param name="left"/>
		<xsl:param name="top"/>
		
		<xsl:call-template name="create-image">
			<xsl:with-param name="parent-style" select="$parent-style"/>
			<xsl:with-param name="width" select="$width"/>
			<xsl:with-param name="height" select="$height"/>
			<xsl:with-param name="left" select="$left"/>
			<xsl:with-param name="top" select="$top"/>
		</xsl:call-template>
		
	</xsl:template>
	
	<xsl:template match="draw:aimage">	
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
						</fo:external-graphic>					
		
	</xsl:template>
			
	<!-- Included objects -->
	<xsl:template match="draw:object">
		
		<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<!-- position -->
			<xsl:attribute name="position">absolute</xsl:attribute>
			<xsl:attribute name="left"><xsl:value-of select="./@svg:x" /></xsl:attribute>
			<xsl:attribute name="top"><xsl:value-of select="./@svg:y" /></xsl:attribute>

			<xsl:attribute name="width"><xsl:value-of select="./@svg:width" /></xsl:attribute>
			<xsl:attribute name="height"><xsl:value-of select="./@svg:height" /></xsl:attribute>

			<xsl:apply-templates select="office:document/office:body/*"/>							

		</fo:block-container>

	</xsl:template>

	<!-- block container -->
	<xsl:template match="draw:text-box">			
		<xsl:param name="parent-width"/>
		<xsl:apply-templates>			
			<xsl:with-param name="parent-width" select="$parent-width"/>
		</xsl:apply-templates>
	</xsl:template>
	
	<xsl:template match="text:tab-stop">
		<xsl:text> &#160;  &#160;</xsl:text>
	</xsl:template>	
	
	<xsl:template match="text:footnote">		
		
		<fo:footnote>
			<fo:inline><xsl:value-of select="text:footnote-citation"/></fo:inline>
			<fo:footnote-body>
				<fo:block>
					<xsl:apply-templates select="text:footnote-body/*"/>											
				</fo:block>
			</fo:footnote-body>
		</fo:footnote>
				
	</xsl:template>	
	
	<xsl:template match="draw:line">		
		<fo:block-container xmlns:fo="http://www.w3.org/1999/XSL/Format" position="absolute">
			<fo:block>
				<fo:instream-foreign-object>
					<svg:svg>
						<xsl:attribute name="viewBox">0 0 0 0</xsl:attribute>
						<xsl:attribute name="width"><xsl:value-of select="$page-width" /></xsl:attribute>
						<xsl:attribute name="height"><xsl:value-of select="$page-height" /></xsl:attribute>
						<svg:line>
							<xsl:for-each select="./@svg:*">
								<xsl:attribute name="{local-name()}"><xsl:value-of select="." /></xsl:attribute>
							</xsl:for-each>

							<!-- style -->
							<xsl:variable name="draw-style-name" select="@draw:style-name" />
							<xsl:variable name="draw-style"
								select="//style:style[@style:name=$draw-style-name]/style:properties" />
							<xsl:attribute name="style">
								<xsl:value-of select="concat('stroke-width:', $draw-style/@svg:stroke-width, ';stroke:', $draw-style/@svg:stroke-color)" />
							</xsl:attribute>
						</svg:line>
					</svg:svg>
				</fo:instream-foreign-object>
			</fo:block>
		</fo:block-container>
	</xsl:template>	
	
	<!-- Hyperlink -->
	<xsl:template match="text:a">
		<fo:basic-link xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<xsl:attribute name="color">blue</xsl:attribute>
			<xsl:attribute name="text-decoration">underline</xsl:attribute>		
			<xsl:attribute name="external-destination"><xsl:value-of select="concat('url(', @xlink:href, ')')"/></xsl:attribute>			
				<xsl:value-of select="."/>						
		</fo:basic-link>

	</xsl:template>
	
	<!-- Text Sequence -->
	<xsl:template match="text:sequence-ref">
		<xsl:value-of select="."/>
	</xsl:template>
	
		<xsl:template name="apply-current-position">
			<xsl:param name="component"/>
			
			<xsl:if test="$component/@svg:y">
				<xsl:attribute name="top"><xsl:value-of select="$component/@svg:y"/></xsl:attribute>
			</xsl:if>
			
			<xsl:if test="$component/@svg:x">
				<xsl:attribute name="left"><xsl:value-of select="$component/@svg:x"/></xsl:attribute>
			</xsl:if>
			
			<xsl:if test="$component/@svg:width">
				<xsl:attribute name="width"><xsl:value-of select="$component/@svg:width"/></xsl:attribute>
			</xsl:if>			
			
			<xsl:if test="$component/@svg:height">
				<xsl:attribute name="height"><xsl:value-of select="$component/@svg:height"/></xsl:attribute>
			</xsl:if>
			
		</xsl:template>	
	
</xsl:stylesheet>