#include "../CPP_DllTest_Main/Plugin.h"
class DllTest :public Plugin
{
public:
	DllTest();
	~DllTest();

	void init() override;
	void update() override;
	void shutdown() override;
};
