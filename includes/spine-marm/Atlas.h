#ifndef SPINE_ATLAS_H_
#define SPINE_ATLAS_H_

#include <spine/BaseAtlas.h>
#include <IwTexture.h>

namespace spine {

class AtlasPage: public BaseAtlasPage {
public:
  AtlasPage() : texture(NULL) {}
  ~AtlasPage() { if (texture) delete texture; }

	CIwTexture *texture;
};

//

class AtlasRegion: public BaseAtlasRegion {
public:
	AtlasPage *page;
};

//

class Atlas: public BaseAtlas {
public:
	Atlas (std::ifstream &file);
	Atlas (std::istream &input);
	Atlas (const std::string &text);
	Atlas (const char *begin, const char *end);

	AtlasRegion* findRegion (const std::string &name);

private:
	virtual BaseAtlasPage* newAtlasPage (std::string name);
	virtual BaseAtlasRegion* newAtlasRegion (BaseAtlasPage* page);
};

} /* namespace spine */
#endif /* SPINE_ATLAS_H_ */
