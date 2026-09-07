#pragma once
class InputStream
{
public:
	virtual char get() = 0;
	virtual bool eof() const = 0;
	virtual ~InputStream() = default;
};

