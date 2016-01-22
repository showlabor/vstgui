//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 4.3
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2015, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "winstring.h"

#if WINDOWS

#include <algorithm>

namespace VSTGUI {

static int kMinWinStringBufferSize = 256;

//-----------------------------------------------------------------------------
IPlatformString* IPlatformString::createWithUTF8String (UTF8StringPtr utf8String)
{
	return new WinString (utf8String);
}

//-----------------------------------------------------------------------------
WinString::WinString (UTF8StringPtr utf8String)
: wideString (0)
, wideStringBufferSize (0)
{
	setUTF8String (utf8String);
}

//-----------------------------------------------------------------------------
WinString::~WinString ()
{
	if (wideString)
		std::free (wideString);
}

//-----------------------------------------------------------------------------
void WinString::setUTF8String (UTF8StringPtr utf8String)
{
	if (utf8String)
	{
		int numChars = MultiByteToWideChar (CP_UTF8, 0, utf8String, -1, 0, 0);
		if ((numChars+1)*2 > wideStringBufferSize)
		{
			if (wideString)
				std::free (wideString);
			wideStringBufferSize = std::max<int> ((numChars+1)*2, kMinWinStringBufferSize);
			wideString = (WCHAR*)std::malloc (static_cast<size_t> (wideStringBufferSize));
		}
		if (MultiByteToWideChar (CP_UTF8, 0, utf8String, -1, wideString, numChars) == 0)
		{
			wideString[0] = 0;
		}
	}
	else if (wideString)
		wideString[0] = 0;
}

} // namespace

#endif // WINDOWS
