#include "object.h"
#include <stdio.h>

Object* createObject()
{
	printf("Creating object\n");

	Object* obj = (Object*)malloc(sizeof(Object));
	assert(obj);

	obj->mf = &objectMemberFunctions;
	obj->vf = &objectVirtualFunctions;

	obj->name = NULLPTR;
	obj->parent = NULLPTR;
	obj->childrenList.head = NULLPTR;
	return(obj);
}

Object* createObjectWithParent(Object* parent)
{
	assert(parent);
	Object* obj = createObject();
	assert(obj);
	obj->mf->SetParent(obj, parent);
	return(obj);
}

void deleteObject(Object* obj)
{
	//printf("Object deleted\n");
	assert(obj);
	if(obj->name != NULLPTR) {
		printf("Object with name \"%s\" deleted\n", obj->name);
		free((void*)obj->name);
	}
	else {
		printf("Object deleted\n");
	}

	// deleting this obj from parent if any
	if(obj->parent != NULLPTR) {
		assert(obj->parent->childrenList.head);

		// finding obj in parent childList
		ChildNode* prevNode = obj->parent->childrenList.head;
		if(prevNode->obj == obj) {
			// if it's first element
			obj->parent->childrenList.head = prevNode->next;
		}
		else {
			// finding currNode and prevNode
			ChildNode* currNode = prevNode->next;
			while(currNode != NULLPTR && currNode->obj != obj) {
				prevNode = currNode;
				currNode = currNode->next;
			}

			// if found - delete from list
			if(currNode->obj == obj) {
				prevNode->next = currNode->next;
			}
		}
	}

	// deleting all obj children objects
	ChildNode* head = obj->childrenList.head;
	while(head != NULLPTR) {
		printf("deleting child...\n");
		ChildNode* pChild = head;
		head = head->next;

		pChild->obj->parent = NULLPTR;
		deleteObject(pChild->obj);

		free((void*)pChild);
	}

	free((void*)obj);
}

void SetObjectParent(Object* self, Object* parent)
{
	assert(self);
	assert(parent);

	self->parent = parent;
	if(parent->childrenList.head == NULLPTR) {
		parent->childrenList.head = (ChildNode*)malloc(sizeof(ChildNode));
		parent->childrenList.head->obj = self;
		parent->childrenList.head->next = NULLPTR;
		return;
	}

	ChildNode* newChildNode = (ChildNode*)malloc(sizeof(ChildNode));
	assert(newChildNode);
	newChildNode->obj = self;
	newChildNode->next = parent->childrenList.head;
	parent->childrenList.head = newChildNode;
}

void SetObjectName(Object* self, const char* name)
{
	assert(self);
	assert(name);
	self->name = strdup(name);
}

void* CloneObject(void* self)
{
	Object* thisObj = (Object*)self;
	Object* cloneObj = createObject();
	assert(thisObj);
	assert(cloneObj);

	cloneObj->mf = thisObj->mf;
	cloneObj->vf = thisObj->vf;
	cloneObj->name = (thisObj->name == NULLPTR) ? NULLPTR : strdup(thisObj->name);

	return(cloneObj);
}