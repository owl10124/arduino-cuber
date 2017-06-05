//this is all pseudocode
bool ready = false;
bool inserted = false;
bool solving = false;
void long_press()
{
    ready = false;
    inserted = false;
    solving = false;
}

void short_press()
{
    if (!ready)
    {
        ready = true;
        return nil;
    }
    else if (!inserted)
    {
        inserted = true;
        return nil;
    }
}

int main()
{
    
}
