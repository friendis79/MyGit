from typing import Union
from fastapi import FastAPI, Path
from pydantic import BaseModel

app = FastAPI() # FastAPI()를 app이라는 이름으로 사용한다.

class Item(BaseModel): # pydantic의 BaseModel을 상속받아 사용한다.
    name: str # name이라는 변수는 필수로 적어주고, string형이여야 한다.
    description: Union[str, None] = None # 설명은 적어도 되고, 적지 않아도 된다.
    price: float # price는 float형으로 필수로 적어주어야 한다.
    tax: Union[float, None] = None # 세금은 float형으로 적거나, None으로 적어도 된다.

@app.put("/items/{item_id}")
async def update_item( #비동기로 함수를 선언한다.
    *, # *표시로 기본값이 없는 변수와, 있는 변수의 순서를 고민안해도 된다.
    item_id: int = Path(title="The ID of the item to get", ge=0, le=1000),
    # item_id는 int형이어야 하고 경로매개변수에 적어주어야한다. 0<= item_id <=1000
    q: Union[str, None] = None,
    item: Union[Item, None] = None,
):
    results = {"item_id": item_id}
    if q:
        results.update({"q": q})
    if item:
        results.update({"item": item})
    return results