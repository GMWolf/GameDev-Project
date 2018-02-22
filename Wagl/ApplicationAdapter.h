#pragma once
class ApplicationAdapter {
public:
	virtual void render() = 0;
	virtual void init();
	virtual void end();

};