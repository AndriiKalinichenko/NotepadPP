#include "precompiledHeaders.h"
#include "RecentlyClosedFiles.h"

RecentlyClosedFiles::RecentlyClosedFiles()
{
	_files = set	<sessionFileInfo, 
					bool (*)(sessionFileInfo, sessionFileInfo)> 
					(_cmpFiles);
}

RecentlyClosedFiles::~RecentlyClosedFiles()
{
	_files.clear();
}

bool RecentlyClosedFiles::add(const sessionFileInfo &fileInfo)
{
	pair <setIterator, bool> res = _files.insert(fileInfo);
	if (res.second == false) {
		_files.erase(fileInfo);
		_files.insert(fileInfo);
	}
	return res.second;
}

bool RecentlyClosedFiles::remove(const sessionFileInfo &fileInfo)
{
	size_t res = _files.erase(fileInfo);
	return (res > 0);
}

void RecentlyClosedFiles::clear()
{
	_files.clear();
}

bool RecentlyClosedFiles::get(const generic_string &fileName, sessionFileInfo &fileInfo)
{
	sessionFileInfo tmpFileInfo(fileName);
	setIterator iter = _files.find(tmpFileInfo);
	if (iter != _files.end()) {
		fileInfo = *iter;
	}
	return (iter != _files.end());
}

bool RecentlyClosedFiles::_cmpFiles(sessionFileInfo f1, sessionFileInfo f2)
{
	return (f1._fileName.compare(f2._fileName) < 0);
}