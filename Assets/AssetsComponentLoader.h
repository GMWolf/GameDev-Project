#pragma once

template<class T>
class AssetsComponentLoader : public ComponentLoader
{
public:
	AssetsComponentLoader(Assets& assets) : assets(assets){
	}

	void load(nlohmann::json& j, void* c) override
	{
		T* t = static_cast<T*>(c);
		t->load(j, assets);
	}
private:
	Assets& assets;
};
