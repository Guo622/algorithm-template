

//��ȡnext����
j = 2, k = next[j - 1];
while (j <= len_ģʽ��)
{
	while (a[j - 1] != a[k] && k)
		k = next[k];
	next[j++] = ++k;
}

//ƥ��
i = j = 1;
while (j <= len_ģʽ�� && i <= len_����)
{
	while (b[i] != a[j] && j)
		j = next[j];
	i++, j++;
}
