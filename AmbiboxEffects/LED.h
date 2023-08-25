// // This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// // PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma once

struct LED
{
	explicit LED( DWORD r = 0, DWORD g = 0, DWORD b = 0 )
		: rgb{ r, g, b }
	{
	}

	LED( const LED& rhs )
	{
		rgb[0] = rhs.rgb[0];
		rgb[1] = rhs.rgb[1];
		rgb[2] = rhs.rgb[2];
	}

	LED& operator = ( const LED& rhs )
	{
		rgb[0] = rhs.rgb[0];
		rgb[1] = rhs.rgb[1];
		rgb[2] = rhs.rgb[2];

		return *this;
	}

	DWORD rgb[3];
};
