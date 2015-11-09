#ifndef _CHANNEL
#define _CHANNEL

///TODO: Implement automatic channel guarding other way as #define's cannot be used inside #defines.

#define CHANNEL(type, name)\
	#ifndef DEF##name##Channel\
	#define DEF##name##Channel\
	type g_##name##Channel;\
	#endif

#define changeChannelValue(name, operator, value)\
	#ifdef DEF##name##Channel\
	g_##name##Channel operator value;\
	#endif

#endif