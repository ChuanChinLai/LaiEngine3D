/*

#if defined(_DEBUG)
#	define ENG_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define ENG_NEW new
#endif



int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
// tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;
_CrtSetDbgFlag(tmpDbgFlag);
auto prt = ENG_NEW int(10);
auto c = new char('a');


*/
