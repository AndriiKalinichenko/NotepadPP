#ifndef SESSION_H
#define SESSION_H

#ifndef PRECOMPILEHEADER_H
#include "precompiledHeaders.h"
#endif //PRECOMPILEHEADER_H

#ifndef M30_IDE_COMMUN_H
#include "Common.h"
#endif //M30_IDE_COMMUN_H

using namespace std;

struct Position
{ 
	int _firstVisibleLine;
	int _startPos;
	int _endPos;
	int _xOffset;
	int _selMode;
	int _scrollWidth;
	Position() : _firstVisibleLine(0), _startPos(0), _endPos(0), _xOffset(0), _scrollWidth(1), _selMode(0) {};
};

struct sessionFileInfo : public Position {
	sessionFileInfo(const TCHAR *fn, const TCHAR *ln, int encoding, Position pos, const TCHAR *backupFilePath, int originalFileLastModifTimestamp) : 
		_encoding(encoding), Position(pos), _originalFileLastModifTimestamp(originalFileLastModifTimestamp) {
		if (fn) _fileName = fn;
		if (ln)	_langName = ln;
		if (backupFilePath) _backupFilePath = backupFilePath;
	};

	sessionFileInfo(generic_string fn) : _fileName(fn), _encoding(-1){};
	
	generic_string _fileName;
	generic_string	_langName;
	vector<size_t> _marks;
	vector<size_t> _foldStates;
	int	_encoding;

	generic_string _backupFilePath;
	time_t _originalFileLastModifTimestamp;
};

struct Session {
	size_t nbMainFiles() const {return _mainViewFiles.size();};
	size_t nbSubFiles() const {return _subViewFiles.size();};
	size_t _activeView;
	size_t _activeMainIndex;
	size_t _activeSubIndex;
	vector<sessionFileInfo> _mainViewFiles;
	vector<sessionFileInfo> _subViewFiles;
};


#endif //SESSION_H