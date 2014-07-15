#pragma once
//#ifndef RECCLOSEDFILES_H
//#define RECCLOSEDFILES_H

// Local includes
#ifndef SESSION_H
#include "Session.h"
#endif //SESSION_H

#ifndef PRECOMPILEHEADER_H
#include "precompiledHeaders.h"
#endif //PRECOMPILEHEADER_H

// Global includes
//#include <windows.h>
//#include <deque>

struct sessionFileInfo;

class RecentlyClosedFiles
{
public:
	RecentlyClosedFiles();
	RecentlyClosedFiles(int maxSize);

	~RecentlyClosedFiles();
	
	// If element already existed function replaces it by new fileInfo
	// however returning false
	bool add(const sessionFileInfo &fileInfo);
	bool remove(const sessionFileInfo &fileInfo);
	void clear();
	// Get whole file info by file name
	// result is stored in fileInfo if function returns true
	// false is returned in case of file not found
	bool get(const generic_string &fileName, sessionFileInfo &fileInfo);

	size_t size() const { return _files.size(); };
	sessionFileInfo &get(size_t idx);

private :
	const int _maxSize;
	deque <sessionFileInfo> _files;

	deque<sessionFileInfo>::iterator _inDeque(const generic_string &fileName);
};

//#endif //RECCLOSEDFILES_H