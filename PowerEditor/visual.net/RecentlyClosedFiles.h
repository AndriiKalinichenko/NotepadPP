#ifndef RECCLOSEDFILES_H
#define RECCLOSEDFILES_H

// Global includes
#include <windows.h>
#include <deque>

// Local includes
#ifndef PARAMETERS_H
#include "Parameters.h"
#endif //PARAMETERS_H

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

private :
	const int _maxSize;
	deque <sessionFileInfo> _files;

	deque<sessionFileInfo>::iterator _inDeque(const generic_string &fileName);
};

#endif //RECCLOSEDFILES_H