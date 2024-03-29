﻿#include <iostream>

using namespace std;

class MyString
{
private:
    //указатель на массив char, хранит символы которые мы передали в наш объект
    char *str;

    int length;
public:

    //конструтор по умолчанию без параметров
    //если просто нужно создать объект класса стринг и пока ничего не присваивать
    MyString()
    {
        str = nullptr;
        length = 0;
    }



    //strlen() считает количество символов в строке пока не наткнется на \0
    //length переменная хранящая колличество символов в строке
    // 
    //конструктор с параметром который принимает указатель на тип чар
    //может принимать любую строку которую мы ему передадим

    //конструктор с параметрами, при создании объекта класса необходимо передать строку которую он будет хранить
    MyString(const char* str)
    {
        //функция strlen() получает количество сиволов в строке которую мы передаем в объект, 
        //для того чтобы знать сколько местор нам нужно будеть выделить в динамичесской памяти под наш новый массив

        
        length = strlen(str);//присвоим значение, которое будет характерезировать колличество символов в строке которую мы приняли,полю length

        //выделяем память для динамического массива где будет храниться наша строка
        //+1 символ так как нужно место в массиве под терминальный ноль

        //с помощью указателя на чар мы создаем новый массив в динамической памяти
        //размером с колличества символов в той строке которую мы передали в конструктор +1 так как нужен терминальный ноль в конце строки
        //потому что strlen() не считает терминальный ноль за символ и она его не учитывает
        this->str = new char[length + 1];//выделяем место в динамической паяти

        //перебираем циклом массивы до тех пор пока в том указателе котрый нам передали в конструкторе есть символы
        // и просто посимвольно их сбрасываем в наш указатель который находится у нас в приват зоне

        for (int i = 0; i < length; i++)
        {
            this->str[i] = str[i];// проходим по элементам 2х массивов и из одного массива присваиваем поэлементно значения в другой массив
        }

        //закрываем все это дело терминирующим нулем, чтобы знать где конец той строки которая у нас и теперь хранится в нашем объекте класса 
        this->str[length] = '\0';//обьявление конца строки
    }





    //деструктор,отвечает за освобождение ресурсов занятых объектом, вызывается  при уничтожении объекта класса
    ~MyString()
    {
        delete[] this->str;
    }


    //конструктор копирования нужен для того, чтобы мы могли один подобный объект нашего класса скопировать в другой и не получить при этом ошибку при работе с динамической памятью
    // потому что по умолчанию такой конструктор копирует все поля абсолютно идентично,
    // 
    // если мы не сделаем конструктор копирования как он реализован ниже то 
    // мы получим ошибку памяти из за того что у нас 2 указателя в объекте из которого мы копировали
    // и в объекте в который мы копировали будут указывать на одну и ту же область динамической памяти
    // а когда 2 таких объекта будут выходить из области видимости какой то функции 
    // у нас 2 раза для одной и той же области, для одной и той же динамической памяти вызовиться деструктор
    // собственно мы попытаемся оператором делит 2 раза освободить ресурсы с одной и той же области памяти
    // что спровоцирует ошибку
    //
    //конструктор копирования, необходим для создания точной копии юбъекта класса но в другой области памяти
    MyString(const MyString &other)
    {   
        length = strlen(other.str);//берем размер того массива который мы принемаем и присваеиваем это значение полю length

        //выделяем новый динамический массив при копировании одного объекта в другой
        this->str = new char[length + 1];//выделяем место в динамической памяти для нового массива чар

        //и поэлементно все это дело копируем чтобы при вызове деструктора не было проблем с динамической памятью
        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];// проходим по элементам 2х массивов и из одного массива присваиваем поэлементно значения в другой массив
        }
        this->str[length] = '\0';//обьявление конца строки
    }




    //перегруженный оператор присваивания практически то же самое что конструктор копирования
    //только мы еще заранее проверяем нет ли у нас в текущем объекте уже каких-то данных
    //и если есть то мы наши ресурсы освобождаем и делаем тоже самое что в нашем конструкторе копирования


    //перегрузка оператора присваивания
    //оператор присваивания должен возвращать ссылку на тип нашего класса
    //это функция которая должна принимать в себя константную ссылку на объект нашего класса
    MyString& operator = (const MyString &other) 
    {
        if (this->str != nullptr)//если наш указатель не nullptr (значит в нем что-то есть)
        {
            delete[]str;//очищаем динамическую память
        }

        length = strlen(other.str);//берем размер того массива который мы принемаем и присваеем значение полю length

        this->str = new char[length + 1];//выделяем место в динамической памяти для нового массива чар
        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];// проходим по элементам 2х массивов и из одного массива присваиваем поэлементно значения в другой массив
        }
        this->str[length] = '\0';//обьявление конца строки

        return *this;//возвращаем разименованный указатель потому что мы возвращаем ссылку на текущий объект нашего класса
    }



    //оператор + нужен для того чтобы выполнить конкотанацию строки

    //перегрузка оператора сложения который будет возвращать не ссылку, а объект MyString, потому что в результате сложения
    //у нас будет создаваться новый объект которому мы будем присваивать в result
    
    MyString operator + (const MyString& other)
    {
        MyString newStr;//создаем новый объект класса

        //так как нам нужно знать какого размера будет указатель который будет хранить строку нам будут нужны 2 переменные
        //  когда мы будем выделять место в нашем новом объекте в его указатель str через оператор new 
        //

        //храниит длинну массива чар который в текущей строчке
        int thisLength = strlen(this->str); 

        //смотрим сколько места занимает строка которую мы передаем
        int otherLength = strlen(other.str); 

        newStr.length = thisLength + otherLength;//присваиваем значение длинны результирующего массива чаров (длины результирующей строки) полю length объекта newStr

        // с помощью оператора new выделяем в нашем новом массиве место равное сумме длин двух массивов плюс 1 так как нужно места для терминирующего нуля
        newStr.str = new char[newStr.length + 1];
        //теперь у нас есть новы массив в котрый мы должны присвоить все элементы из двух массивов из которых мы складываем новую строчку
        //используем два цикла
        
        //первый цикл переберет массив который находится в this
        //и присвоить в наш новый объект все свои чары 
        int i = 0;//nfr как во втором цикле i должно начинаться не с нуля а с 5го элемента чтобы конечный масиив не перезаписывался а дозаписался
        for (; i < thisLength; i++)
        {
            newStr.str[i] = this->str[i];
        }

        //второй цикл будет помещать обьекты второго массива в новую строку
        //yj мы должны здесь итерироваться с помощью оператора i
        for (int j = 0; j < otherLength; j++, i++)
        {
            newStr.str[i] = other.str[j];
        }
        //после того как все элементы помещены в новый массив, добавляем терминальный ноль для того чтобы обозначить коенец строки
        newStr.str[newStr.length]='\0';
        //теперь нужно объект который мы создали вернуть как результат работы оператора + (нашей функции)
        return newStr;
    }
    void print() {
        cout << str; 
    }

    //метод возврвшающий колличество символов(длинну строки), фактически он похош на геттер
    //но так как нигде не пишут гетсайз или гетленз для строк, метод будет просто Length()
    int Length() 
    {
        //заботимся о том чтобы хранить заранее информацию о нашей строке, 
        //чтобы каждый раз при обращении к методу ленз заново не бежать и считаь это колличество
        //чтобы было меньще накладок на производительность
        return length;
    }
    //перегрузка оператора равенства ==()
    //так как мы сравниваем 2 объекта то фактический объект который мы принимаем как входящий параметр при перегрузке оператора
    //обычно пишут так const потом тип данных с  котрым мы хотим сравнивать MyString и далее ссылка & на объект other с которым мы будем сравнивать 
    //константная ссылка на тип данных значит что мы не копируем объект а просто заглядываем по какому то адресу и смотрим на состояние полей этого объекта
    //поменять мы там ничего не можем потому что константная ссылка
    //а ссылка именно потому что нам не нужно сюда копировать весь объект и засорять озу, тратить на это какие-то ресурсы на операции копирования
    //мы можем просто посмотреть что там лежит, по этому мы передаем по ссылке
    // 
    //что мы должны сделать для того чтобы понять две строки между собой равны или нет?
    //прежде чем писать какой-то код нам нужно сначало логически подумать как это сделать
    //если в2-х строчках разное колличество символов, понятное дело что строчки вообще между собой не равны
    //Что подразумевается под равенством строк? Этот значит что у нас два абсолютно идентичных слова
    //то есть если бы у нас было два слова Hello то понятно что они одинаковы,
    //раз у нас тот момент когда 2 строки имеют разное колличество символов уже явно дает понять что строчки разные
    //нам уже не нужно посимвольно проверять, сразу можно сделать вывод что они не равны
    // 
    //поэтому если поле length текущего объекъта, о том что это текущий обьект нам говорит указатель this, не равно полю length орбьекта other(other.length)
    //который мы сюда передаем как параметр то мы уже сразу можем сделать вывод что эти 2 строки неравны поэтому можем сделать сразу возврат значения false
    //если поля равны то пробегаем по строкам через for так как у них одинаковое колличество символов то мы можем итерироваться столько раз сколько символов либо  в одной либо в другой строчке 
    //поэтому можно взять просто поле length, так ка мы находимся в классе то оно нам подойдет, но для того чтобы ввести ясность можно написать вот так this->length
    //в цикле пишем еще одно условие: если хотябы один элементв массиве который именно в текущем классе, который у нас хранит все чары будет неравен, тому элементу который находится в тойже позиции
    //только в объекте other который мы передали ему как параметр, то мы уже сразу можем понять что наши объекты между собой неравны и можем сразу вернуть false
    //есть маленький ньюанс, не все ветви этого кода возвращают значение, если мы видим что переменные не равны между собой, мы возвращаем false 
    //и если мы находим хотябы 1 символ который в той же позиции не равен символу в другом объекте, мы возвращаем false и сразу выходим, но если оба условия не выполнилось
    //и длинна у нас одинаковая то логично что наши строки будут тоже одинаковые, поэтому  в этом случае мы возвращаем true
    //nj есть мы дошли до такого момента когда мы точно можем сказать что в этом случае наши с вами строчки абсолютно идентичны
    bool operator ==(const MyString &other) 
    {
        if (this->length != other.length)
        {
            return false;
        }

        for (int i = 0; i < this->length; i++)
        {
            if (this->str[i] != other.str[i])
            {
                return false;
            }
        }
        return true;
    }
    //в данном случее метод operator !=() рекурсивно вызовет метод operator==() и вернет результат метода  operator==()
    //но операция не равно по своей сути инверсивна и возвращает инверсированный результат, поэтому если мы получим в методе operator==() тру то в метод operator !=() вернется фолс
    bool operator !=(const MyString& other)
    {
        return (!(this->operator==(other)));
    }
    //перегрузка оператора [] для получения символа хронящегося под индексом массива, индекс задаем как входной параметр
    //чтобы можно было менять букву в массиве строк по индексу нужно возвращать ссылку
    char& operator [](int index) 
    {
        return this->str[index];
    }

    //конструктор перемещения нужен для того чтобы существенно оптимизировать код и ускорить работу программы
    // 
    //при конкотанации когда мы создаем новую переменную которая будет содержать часть строчек, по сути нужно создать новый объект
    //мы его создаем и как результат есть новый объект Hello World когда возвращается его значение
    //вместо того чтобы просто сказать переменной result что вот мы создали новый объект ты просто возми его и используй
    //мы так не делаем, а попадаем в конструктор копирования где создается новая область динамической памяти
    //и мы поэлементно перетаскиваем все буквы с того объекта 
    //
    //по сути он указывает переменной на обьект чтобы переменная его сразу использвала
    //синтаксис чем-то похож на конструктор копирования

    //вместо того чтобы принять ссылку на объект, нам нужно принять ссылку на ссылку на обьект
    //такая конструкция позволит сразу сказать что мы берем обьект и сразу используем его
    MyString(MyString&& other)
    {
        //нашему текущему объекту присваиваем значение переменной length того объекта который мы принимаем
        this->length = other.length;
       //далее просто берем и в наш указатель который указывает на массив в динамической памяти присвоить адрес
        //такого же самого массива только в объекте other
        //таким образом мы его не копируем поэлементно а просто говорим
        //ну вон он теперь по тому адресу ты теперь на него ссылайся и сним работай
        this->str = other.str;
        //для того чтобы наш объект не уничтожился нам нужно запретить удалять эти данные
        //обращаемся к этому объекту к его указателю и присваиваем нулпоинтер таким образом мы запрещаем удалять данные на которые ссылается
        // так как нам нужно внести изменения в объект other то ключевое слово const в сигнатуре не нужно
        other.str = nullptr;
    }

    void strLength(char* str)
    {
        int counter = 0;

        while (str[counter] != '\0')
        {
            counter++;
        }
        cout<< counter;
};





 

int main() 
{
    
    MyString str("Hello");//инициализация str строкой "Hello" при помощи конструктора с параметром
    MyString str2("World");//инициализация str2 строкой "World" при помощи конструктора с параметром
    MyString result = str + str2;//конокотанация при помощи перегруженного оператора +
    //result.print();
    cout << str.Length()<<endl;
    cout << str2.Length()<<endl;
    cout << result.Length() << endl;

    bool equal = str == str2;// == фактически означает str.operator==(str2), str в данном случае это this объект а other объект это тот который мередаем параметром это str2
    //просто компилятор позволяет это все не писать (bool equal = str.operator==(str2)), а просто можно писать так  (bool equal = str == str2;) чтобы было проще

    str.print();
    cout << endl;
    str[0]='S';
    str.print();
    

    return 0;
}

