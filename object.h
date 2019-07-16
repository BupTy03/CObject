#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NULLPTR ((void*)0)

struct Object;

typedef struct ObjectMemberFunctions {
	void(*SetName)(struct Object*, const char*);
	void (*SetParent)(struct Object* self, struct Object* parent);
} ObjectMemberFunctions;

typedef struct ObjectVirtualFunctions {
	void* (*Clone)(void*);
} ObjectVirtualFunctions;

typedef struct ChildNode {
	struct ChildNode* next;
	struct Object* obj;
} ChildNode;

typedef struct Object {
	// member functions
	const ObjectMemberFunctions const* mf;
	// virtual member functions
	const ObjectVirtualFunctions* vf; 

	// fields
	const char* name;
	struct Object* parent;

	struct ChildrentList {
		ChildNode* head;
	} childrenList;
} Object;

// member functions
void SetObjectName(Object* self, const char* name);
void SetObjectParent(Object* self, Object* parent);

// virtual functions
void* CloneObject(void* self);

static const ObjectMemberFunctions objectMemberFunctions = {
	SetObjectName,
	SetObjectParent
};

static const ObjectVirtualFunctions objectVirtualFunctions = {
	CloneObject
};

// free functions
Object* createObject();
Object* createObjectWithParent(Object* parent);
void deleteObject(Object* obj);

#endif // !OBJECT_H