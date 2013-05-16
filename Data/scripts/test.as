void main(){

	ClassTest testClass;
	
	print("Hello world");
	something();
	print("5 + 10 = " + testClass.sum(5 , 10));
}

void something(){
	instantiateObject();
}

class ClassTest{
	int sum(int a, int b)const{
		return a + b;
	}
}

void onLoadLevel(int levelNumber, string levelName){
	print("Loading level number " + levelNumber + " with name " + levelName);
	
	//create some scenery
	if(levelNumber == 1){
		
	}
}