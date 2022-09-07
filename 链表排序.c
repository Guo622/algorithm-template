void sort_list_by_pointer_v2(struct s_list **headp)
{
    struct s_list *prior1,*prior2,*p1,*p2,*t;
    int i=0;
    p1=(struct s_list *)malloc(sizeof(struct s_list));
    p1->next=*headp;
    (*headp)=prior1=p1;
    for(p1=prior1->next;p1->next!=NULL;prior1=p1,p1=p1->next)
        for(p2=p1->next,prior2=p1;p2!=NULL;prior2=p2,p2=p2->next)
            if(p1->data>p2->data)
    {

        t=p2->next;
        prior1->next=p2;
        prior2->next=p1;
        p2->next=p1->next;
        p1->next=t;
        t=p1;p1=p2;p2=t;
    }
    p1=(*headp);
    (*headp)=(*headp)->next;
    free(p1);
}
