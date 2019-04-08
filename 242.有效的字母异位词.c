1.��ϣ��

bool isAnagram(char* s, char* t) {
    int hash[26] = {0}, len1 = strlen(s), len2 = strlen(t);

    // �ù�ϣ���ж������ַ����е��ַ����ִ����Ƿ�һ�¡�
    for (int i = 0; i < len1; i++)
        hash[s[i]-'a']++;    
    for (int i = 0; i < len2; i++)
        hash[t[i]-'a']--;  
    for (int i = 0; i < 26; i++) {
        if (hash[i] != 0)
            return false;
    }
    
    return true;
}


2.����

// ���ź���(����)��
int compare(const void* a, const void* b) {
    return (*(char*)a)-(*(char*)b);
}

// ��������ж����ַ����Ƿ���ȡ�
bool isAnagram(char* s, char* t) {
    if (strlen(s) != strlen(t))
        return false;
    else {
        qsort(s, strlen(s), sizeof(char), compare);    
        qsort(t, strlen(t), sizeof(char), compare);  
        
        if (strcmp(s, t) == 0)
            return true;
        else
            return false;
    }
}