# DirectX11CustomTool

โจmade by:  KYR

๐ blog : https://odlram.tistory.com/

> ์ ์ ์ ํ๋ํ๋ ์ฐ์ด์ ๋ํ์ ๋ง๋ค๊ธฐ๊ฐ ๊ท์ฐฎ์์, ๊ฐ์ฒด์งํฅ(2) ์ ๊ณต ์๊ฐ์ ๋ฐฐ์ด ๊ฐ๋๋ค์ ํ์ฉํ์ฌ, ๋ค์ํ ๋ํ์ ๋ง๋ค ์ ์๋ ํด๋์ค๋ฅผ ๋ง๋ค์ด๋ณด์์ต๋๋ค.



๐ค **Class**

```yaml
Shape.h
|- Square.h
|- Circle.h
```



๐ค **Example**

โ ์ ๊ณต ๊ต์๋๊ป์ ์ ๊ณตํด ์ฃผ์  **DirectX11 Tutorial** ์คํฌ๋ฆฝํธ๋ฅผ ๊ธฐ๋ฐ์ผ๋ก ์์ฑ๋ ์์ ์๋๋ค.

`1. ํค๋ํ์ผ ์ถ๊ฐ`

```c++
#include "Square.h"
#include "Circle.h"
```



`2. ๊ฐ์ฒด ์ ์ธ`

์๋จ์ ๊ฐ์ฒด๋ฅผ ๋ฏธ๋ฆฌ ์ ์ธ ํด์ฃผ์์ผ ํฉ๋๋ค.

```c++
Circle* test;
```



`3. InitGraphic`

๋ํ ํค๋๋ฅผ ์ถ๊ฐํ์๋ฉด ํ ์ค๋ก ๊ฐํธํ๊ฒ ๋ํ์ ์์ฑํ  ์ ์์ต๋๋ค.๐

๐ Circle ์์ฑ

```c++
new Circle(Position, Radian , devcon, dev,Color1,  Color2, Color2,isFilled);
```

๐ Square ์์ฑ

```c++
new Square(Position, Dimension , devcon, dev,Color1,  Color2, Color2,isFilled);
```

<์์>

```c++
void InitGraphics()
{   
  test = new Circle({ 0,0 }, 1, devcon, dev,
 D3DXCOLOR(0.839f, 0.635f, 0.909f, 1.0f), 
 D3DXCOLOR(0.925f, 0.847f, 0.952f, 1.0f),
 D3DXCOLOR(0.898f, 0.847f, 0.913f, 1.0f),false);
}
```

๋ง์ง๋ง์ ์๋ bool ํ ๋งค๊ฐ๋ณ์๋ ๋ํ์ ๋ด๋ถ๋ฅผ ์์ผ๋ก ์ฑ์ธ์ง์๋์ง์ ๋ํ ์ค์ ์๋๋ค.

true -> ๋ด๋ถ์ ์ ์ฑ์

<img src="https://user-images.githubusercontent.com/63442636/141048219-8d9b98a6-8d52-407e-9e34-63e2292af50c.gif"/>

false-> ๋ด๋ถ์ ์ ์ฑ์ฐ์ง ์์

<img src="https://user-images.githubusercontent.com/63442636/141047962-10377082-034f-4f0a-ab96-7eae9528bd73.gif"/>



`4. Render Frame`

๐ ํ์ 

```c++
test->rotation(ANGLE::Y, 91.0f);
test->rotation(ANGLE::Y, Time);
test->rotation(ANGLE::Z,Time);
```

๐ ์ด๋

```c++
test->translate(2.0f, 0.0f, 0.0f);
```



๐ ์ค์ผ์ผ

```c++
test->scaling(1.0f, 1.0f, 1.0f);
```



โญ ๋ชจ๋  ํ๋ ฌ ๊ณ์ฐ ๋ฐ ์นด๋ฉ๋ผ ๋ฑ๋ฑ ์๋ฐ์ดํธ

```c++
devcon->UpdateSubresource(pCBuffer, 0, 0, test->update(test->metGatRotate(), matView,matProjection), 0, 0);
```



โญ render

```c++
 test->render();
```



