# DirectX11CustomTool

✨made by:  KYR

💖 blog : https://odlram.tistory.com/

> 정점을 하나하나 찍어서 도형을 만들기가 귀찮아서, 객체지향(2) 전공 시간에 배운 개념들을 활용하여, 다양한 도형을 만들 수 있는 클래스를 만들어보았습니다.



🤍 **Class**

```yaml
Shape.h
|- Square.h
|- Circle.h
```



🤍 **Example**

✔ 전공 교수님께서 제공해 주신 **DirectX11 Tutorial** 스크립트를 기반으로 작성된 예제입니다.

`1. 헤더파일 추가`

```c++
#include "Square.h"
#include "Circle.h"
```



`2. 객체 선언`

상단에 객체를 미리 선언 해주셔야 합니다.

```c++
Circle* test;
```



`3. InitGraphic`

도형 헤더를 추가하시면 한 줄로 간편하게 도형을 생성할 수 있습니다.😊

📌 Circle 생성

```c++
new Circle(Position, Radian , devcon, dev,Color1,  Color2, Color2,isFilled);
```

📌 Square 생성

```c++
new Square(Position, Dimension , devcon, dev,Color1,  Color2, Color2,isFilled);
```

<예시>

```c++
void InitGraphics()
{   
  test = new Circle({ 0,0 }, 1, devcon, dev,
 D3DXCOLOR(0.839f, 0.635f, 0.909f, 1.0f), 
 D3DXCOLOR(0.925f, 0.847f, 0.952f, 1.0f),
 D3DXCOLOR(0.898f, 0.847f, 0.913f, 1.0f),false);
}
```

마지막에 있는 bool 형 매개변수는 도형의 내부를 색으로 채울지아닐지에 대한 설정입니다.

true -> 내부에 색 채움

<img src="https://user-images.githubusercontent.com/63442636/141048219-8d9b98a6-8d52-407e-9e34-63e2292af50c.gif"/>

false-> 내부에 색 채우지 않음

<img src="https://user-images.githubusercontent.com/63442636/141047962-10377082-034f-4f0a-ab96-7eae9528bd73.gif"/>



`4. Render Frame`

📌 회전

```c++
test->rotation(ANGLE::Y, 91.0f);
test->rotation(ANGLE::Y, Time);
test->rotation(ANGLE::Z,Time);
```

📌 이동

```c++
test->translate(2.0f, 0.0f, 0.0f);
```



📌 스케일

```c++
test->scaling(1.0f, 1.0f, 1.0f);
```

