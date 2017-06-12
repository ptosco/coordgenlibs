#############################################################################
# Makefile for building: coordgen_standalone.app/Contents/MacOS/coordgen_standalone
# Generated by qmake (3.0) (Qt 5.6.2)
# Project:  coordgen_standalone.pro
# Template: app
# Command: /software/lib/Darwin-x86_64/qt-5.6.2/bin/qmake -spec /software/lib/Darwin-x86_64/qt-5.6.2/mkspecs/macx-xcode -o coordgen_standalone.xcodeproj/project.pbxproj coordgen_standalone.pro
#############################################################################

MAKEFILE      = project.pbxproj

MOC       = /software/lib/Darwin-x86_64/qt-5.6.2/bin/moc
UIC       = 
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DSTUB_INTEGRATION -DQT_GUI_LIB -DQT_CORE_LIB
INCPATH       = -I. -I. -I/software/lib/Darwin-x86_64/qt-5.6.2/lib/QtGui.framework/Headers -I/software/lib/Darwin-x86_64/qt-5.6.2/lib/QtCore.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/AGL.framework/Headers -I/software/lib/Darwin-x86_64/qt-5.6.2/mkspecs/macx-clang -F/software/lib/Darwin-x86_64/qt-5.6.2/lib
DEL_FILE  = rm -f
MOVE      = mv -f

preprocess: compilers
clean preprocess_clean: compiler_clean

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compilers:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

