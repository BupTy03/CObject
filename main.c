#include "object.h"

#include <stdio.h>

// Apple inherits Object
typedef struct Apple
{
	Object* base;
} Apple;

// overriding virtual function Clone
void* CloneApple(void* self)
{
	Apple* thisObj = (Apple*)self;
	assert(thisObj);

	Apple* pResult = (Apple*)malloc(sizeof(Apple));
	assert(pResult);

	pResult->base = objectVirtualFunctions.Clone(thisObj->base);
	return pResult;
}

// overriding virtual functions of base class
static const ObjectVirtualFunctions appleBaseVirtualFunctions = {
	CloneApple
};

Apple* createApple()
{
	Apple* pResult = (Apple*)malloc(sizeof(Apple));
	assert(pResult);

	pResult->base = createObject();
	pResult->base->vf = &appleBaseVirtualFunctions;

	return pResult;
}

void deleteApple(Apple* apple)
{
	assert(apple);
	deleteObject(apple->base);
	free((void*)apple);
}

int main(int argc, char* argv[])
{
	/*{
		Object* pObj = createObject();
		pObj->mf->SetName(pObj, "NewObject");

		Object* pClone = (Object*)pObj->vf->Clone(pObj);
		printf("Cloned object name: %s\n", pClone->name);
		pClone->mf->SetParent(pClone, pObj);
		pClone->mf->SetName(pClone, "ClonedObject");

		Object* pChildObj = createObjectWithParent(pObj);
		pChildObj->mf->SetName(pChildObj, "ChildObject");

		// deletes pObj and all his children(pClone and pChildObj)
		deleteObject(pObj);
	}*/

	Apple* apple1 = createApple();
	apple1->base->mf->SetName(apple1->base, "Apple 1");
	printf("Apple name: %s\n", apple1->base->name);

	Apple* apple2 = (Apple*)apple1->base->vf->Clone(apple1);
	printf("Cloned apple name: %s\n", apple2->base->name);

	// TODO: virtual destructor for Object
	deleteApple(apple1);
	deleteApple(apple2);
	return(0);
}