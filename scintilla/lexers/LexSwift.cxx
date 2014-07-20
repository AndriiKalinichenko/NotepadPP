#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "CharacterSet.h"
#include "LexerModule.h"
#include "OptionSet.h"
#include "SparseState.h"
#include "SubStyles.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla
#endif 

static const char * const swiftWordListDesc[] = {
	0,
};


static void ColouriseSwiftDoc(unsigned int startPos, int lengthDoc, int initStyle,WordList * KeyWordList[], IDocument *pAccess){
	styler.startAt(startPos);
	int state = initStyle;

	CharacterSet setOperator(CharacterSet::setNone, "#$&'()*+,-./:;<=>@[]^{}");
	CharacterSet setNumber(CharacterSet::setDigits, ".-+eE");
	CharacterSet setWord(CharacterSet::setAlphaNum, "_", 0x80, true);

	int curLine = styler.GetLine(startPos);
	int curLineState = curLine > 0 ? styler.GetLineState(curLine - 1) : 0;

	StyleContext sc(startPos, length, initStyle, styler);
	
	bool isLineComment = false;

	for (; sc.More(); sc.Forward()) {
		if (sc.atLineEnd) {
			curLine = styler.GetLine(sc.currentPos);
			styler.SetLineState(curLine, curLineState);
		}
		switch (sc.state) {
			case SCE_SWIFT_NUMBER:
				if (!setNumber.Contains(sc.ch) || (sc.ch == '.' && sc.chNext == '.')) {
					sc.SetState(SCE_SWIFT_DEFAULT);
				} 
			case SCE_SWIFT_COMMENT:
				if (sc.Match('*','/') || (sc.atLineStart && isLineComment)){
					sc.setState(SCE_SWIFT_DEFAULT);
				}
			case SCE_SWIFT_STRING:
				if (sc.ch == '"'){
					sc.setState(SCE_SWIFT_DEFAULT);
				}
			case SCE_SWIFT_VARIAVLE:
				if (!setWord.Contains(sc.ch)){
					sc.setState(SCE_SWIFT_DEFAULT);
				}
		}

		if (sc.state == SCE_SWIFT_DEFAULT){
			if (setNumber.Contains(sc.ch)){
				sc.setState(SCE_SWIFT_NUMBER);
			}
			if (setWord.Contains(sc.ch)){
				sc.setState(SCE_SWIFT_VARIABLE);
			}
			if (sc.ch == '"'){
				sc.setState(SCE_SWIFT_STRING);
			}
			if (sc.ch == '#'){
				sc.setState(SCE_SWIFT_COMMENT);
				isLineComment = true;
			}
			if (sc.Match('/','*')){
				sc.setState(SCE_SWIFT_COMMENT);
				sc.Forward();
			}
		}
	}
}

LexerModule lmSwift(SCLEX_SWIFT, ColouriseSwiftDoc,"swift",swiftWordListDesc);
