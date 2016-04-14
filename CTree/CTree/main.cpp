#include "Math.h"
#include "Tree.h"

int main()
{
	Math test;
    test.PutStr(test.GetEquation());
    test.PutStr(test.PrepareEquation());
	CNode* node = test.GetExp();
	node -> GoDump(0);
    //print_equation(node);
    print_tree(node);
    std::cout <<std::endl;
	delete node;
	return 0;
}

/*
+	1) мусор из папки 
+	2) CodeStile и настройки Subl 
+	3) Include
++	4) Сделать функцию GetEqv() и PrepereEqv(){удаляет пробелы и каидает exception, а так же возращает скопированную строку}
+	5) Exception
	6) нестандартный конструктор*/