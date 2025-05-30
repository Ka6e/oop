#pragma once
#include <vector>
#include <memory>
#include "../include/CHttpUrl.h"
#include <iostream>

class UrlManager
{
public:
	void ReadUrls();
	void PrintUrls() const;
private:
	std::vector<std::shared_ptr<CHttpUrl>> m_urls;
};
