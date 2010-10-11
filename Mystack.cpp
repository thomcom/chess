
#include "./defs.h"
#include "./Mystack.h"

Mystack::Mystack()
{
	top = NULL;
       	size = 0;
}

void Mystack::push(shape_ptr p)
{
	if(size==0)
	{
		top = p;
		top->next=NULL;
		size++;
	}
	else
	{
		p->next=top;
		top=p;
		size++;
	}
	
}

shape_ptr Mystack::erase(int subject)
{
	shape_ptr p = top;
	if(p->ID==subject)
	{
		top = p->next;
		size--;
		return p;
	}
	else
	{	
		shape_ptr pParent = top;
		while(p->next!=NULL)
		{
			p = p->next;
			if(p->ID==subject)
			{
				pParent->next = p->next;
				size--;
				return p;
			}
			pParent = pParent->next;
		}
	}
	printf("Mystack::erase failed to find selected item.\n"
			"Returns NULL, report to system administrator.\n");
	return NULL;
}

shape_ptr Mystack::find(int subject)
{
	if(size==0) return 0;
	shape_ptr p = top;
	while(p->next!=NULL)
	{
		if(p->ID==subject) return p;
		else p = p->next;
	}
	if(p->ID==subject) return p;
	return 0;
}

shape_ptr Mystack::pop()
{
	/* System assumes user checks size of stack before popping */
	shape_ptr p = top;
	top = p->next;
	size--;
	return p;
}

shape_ptr Mystack::getTop()
{
	/* System assumes user checks size of stack before topping */
	return top;
}

int Mystack::length()
{
	return size;
}

