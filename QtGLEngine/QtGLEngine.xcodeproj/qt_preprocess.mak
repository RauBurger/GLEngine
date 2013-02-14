#############################################################################
# Makefile for building: QtGLEngine.app/Contents/MacOS/QtGLEngine
# Generated by qmake (2.01a) (Qt 4.7.0) on: Mon Dec 13 16:58:19 2010
# Project:  QtGLEngine.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.7/mkspecs/macx-xcode -o QtGLEngine.xcodeproj/project.pbxproj QtGLEngine.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.7/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I. -I. -I. -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -F/Library/Frameworks
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_canvas.cpp ./ui_canvas.h
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_canvas.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_canvas.cpp
moc_canvas.cpp: Object.h \
		cubeprimitive.h \
		Camera.h \
		canvas.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ canvas.h -o moc_canvas.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_canvas.h
compiler_uic_clean:
	-$(DEL_FILE) ui_canvas.h
ui_canvas.h: canvas.ui
	/Developer/Tools/Qt/uic canvas.ui -o ui_canvas.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

