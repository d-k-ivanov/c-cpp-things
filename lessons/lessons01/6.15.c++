/*	Что делает следующий пример. Зачем кому-то может потребовать подобный код */

void send(int *to, int *from, count)
{
	int n = (count + 7) / 8;
	switch(count%8) 
	{
		case 0:	do {	*to = *from++;
		case 7:		*to = *from++;
		case 6:		*to = *from++;
		case 5:		*to = *from++;
		case 4:		*to = *from++;
		case 3:		*to = *from++;
		case 2:		*to = *from++;
		case 1:		*to = *from++;
				} while(--n > 0);
	}
}

/* Метод Даффа (устройство Даффа, Duff's device) - оптимизированный цикл ввода-вывода */

