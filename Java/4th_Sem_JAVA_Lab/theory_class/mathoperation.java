class mathoperation{
	static float mult(float x, float y){
		return x*y;
	}
	static float div(float x, float y){
		return x/y;
	}
}

class mathapplication {
	public static void main(String args[ ]) {
		float a = mathoperation.mult(4.0f, 3.6f);
		float b = mathoperation.div(4.0f, 3.6f);
	}
}
