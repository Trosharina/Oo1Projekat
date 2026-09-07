#include "OutputStream.h"

void OutputStream::write(const string& str)
{
	for (char c : str) put(c);
}