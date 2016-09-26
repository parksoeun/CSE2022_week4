/*****************************************
�ۼ���: 2015112094 �ڼ���
�ۼ���¥: 2016.09.26
*****************************************/


#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

//���� ��� �Լ�
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.

//�� ���� �մ� ������ �׸��� �Լ�
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) { //�ݺ��� �ȿ��� �� ���� x��ǥ�� ���� �� �и� 0�� �Ǿ� ������ ���� ���� �����ϱ� ����
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

//���� ��(�׵θ� ��)�� �׸��� ���� �Լ� (i0,j0 = ���� �߽� ��ǥ)
void drawCircle(const int& i0, const int& j0, const float& red, const float& green, const float& blue) {
	int r = 50; //���� ������
	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r);
			int m = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 3)*(r - 3));
			if (n < 0 && m>0) //�� ���� ����
				drawPixel(i, j, red, green, blue);
		}
	}
}

//���� ��(���׸� ��)�� �׸��� ���� �Լ� (i0,j0 = ���� �߽� ��ǥ)
void drawCircle_b(const int& i0, const int& j0, const float& red, const float& green, const float& blue) {
	int r = 20; //���� ������
	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r);
			int m = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 5)*(r - 5));
			if (n < 0 && m>0) //�� ���� ����
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		}
	}
}

void drawOnPixelBuffer(GLFWwindow *window)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing



	//�밢��
	for (int l = 0; l < 5; l++) {
		drawLine(50, 350 + l, 100, 400 + l, 1.0f, 0.0f, 0.0f);
	}

	//���ѿ�
	drawCircle_b(200, 380, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��

											  //�� �簢��
	drawLine(300, 410, 350, 410, 1.0f, 0.0f, 0.0f);
	drawLine(350, 360, 350, 410, 1.0f, 0.0f, 0.0f);
	drawLine(300, 360, 350, 360, 1.0f, 0.0f, 0.0f);
	drawLine(300, 360, 300, 410, 1.0f, 0.0f, 0.0f);


	//������
	drawLine(420, 360, 470, 410, 1.0f, 0.0f, 0.0f);
	drawLine(420, 410, 470, 360, 1.0f, 0.0f, 0.0f);

	//�Ʒ� ȭ��ǥ
	drawLine(550, 360, 550, 410, 1.0f, 0.0f, 0.0f);
	drawLine(530, 370, 550, 360, 1.0f, 0.0f, 0.0f);
	drawLine(550, 360, 570, 370, 1.0f, 0.0f, 0.0f);

	//������ ȭ��ǥ
	drawLine(50, 100, 100, 100, 1.0f, 0.0f, 0.0f);
	drawLine(90, 90, 100, 100, 1.0f, 0.0f, 0.0f);
	drawLine(90, 110, 100, 100, 1.0f, 0.0f, 0.0f);

	//���ĺ� A
	drawLine(180, 120, 220, 120, 1.0f, 0.0f, 0.0f);
	for (int m = 0; m<3; m++) //�缱�� ��� ���� �����̵Ǿ� �׵θ��� �� ���ϰ� �ϱ� ���Ͽ� �ݺ��� ���
		drawLine(160, 80 + m, 200, 150 + m, 1.0f, 0.0f, 0.0f);
	for (int n = 0; n<3; n++) //�׵θ��� �� ���ϰ� �ϱ� ���Ͽ� �ݺ��� ���
		drawLine(200, 150 + n, 240, 80 + n, 1.0f, 0.0f, 0.0f);

	//����
	drawLine(330, 80, 330, 130, 1.0f, 0.0f, 0.0f);

	//���� ȭ��ǥ
	drawLine(420, 100, 470, 100, 1.0f, 0.0f, 0.0f);
	drawLine(420, 100, 430, 110, 1.0f, 0.0f, 0.0f);
	drawLine(420, 100, 430, 90, 1.0f, 0.0f, 0.0f);

	//���� ȭ��ǥ
	drawLine(550, 80, 550, 140, 1.0f, 0.0f, 0.0f);
	drawLine(540, 130, 550, 140, 1.0f, 0.0f, 0.0f);
	drawLine(550, 140, 560, 130, 1.0f, 0.0f, 0.0f);



	//�׵θ� ��
	drawCircle(75, 385, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(200, 385, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(325, 385, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(445, 385, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(550, 385, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(75, 100, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(200, 100, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(325, 100, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(445, 100, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��
	drawCircle(550, 100, 1.0f, 0.0f, 0.0f); //���� �߽��� �Է��ϰ� ���� �׸��� �Լ� ȣ��

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	double f = (xpos - 75)*(xpos - 75) + (ypos - 95)*(ypos - 95) - 50 * 50;

	if (f <= 0.0)
		drawCircle(75, 385, 0.0f, 0.0f, 1.0f);

	double a = (xpos - 200)*(xpos - 200) + (ypos - 95)*(ypos - 95) - 50 * 50;

	if (a <= 0.0)
		drawCircle(200, 385, 0.0f, 0.0f, 1.0f);

	double b = (xpos - 325)*(xpos - 325) + (ypos - 95)*(ypos - 95) - 50 * 50;

	if (b <= 0.0)
		drawCircle(325, 385, 0.0f, 0.0f, 1.0f);

	double c = (xpos - 445)*(xpos - 445) + (ypos - 95)*(ypos - 95) - 50 * 50;

	if (c <= 0.0)
		drawCircle(445, 385, 0.0f, 0.0f, 1.0f);

	double d = (xpos - 550)*(xpos - 550) + (ypos - 95)*(ypos - 95) - 50 * 50;

	if (d <= 0.0)
		drawCircle(550, 385, 0.0f, 0.0f, 1.0f);

	double e = (xpos - 75)*(xpos - 75) + (ypos - 380)*(ypos - 380) - 50 * 50;

	if (e <= 0.0)
		drawCircle(75, 100, 0.0f, 0.0f, 1.0f);

	double g = (xpos - 200)*(xpos - 200) + (ypos - 380)*(ypos - 380) - 50 * 50;

	if (g <= 0.0)
		drawCircle(200, 100, 0.0f, 0.0f, 1.0f);

	double h = (xpos - 325)*(xpos - 325) + (ypos - 380)*(ypos - 380) - 50 * 50;

	if (h <= 0.0)
		drawCircle(325, 100, 0.0f, 0.0f, 1.0f);

	double z = (xpos - 445)*(xpos - 445) + (ypos - 380)*(ypos - 380) - 50 * 50;

	if (z <= 0.0)
		drawCircle(445, 100, 0.0f, 0.0f, 1.0f);

	double y = (xpos - 550)*(xpos - 550) + (ypos - 380)*(ypos - 380) - 50 * 50;

	if (y <= 0.0)
		drawCircle(550, 100, 0.0f, 0.0f, 1.0f);

	//Ŀ���� ��� ������ �ٲ�




	//TODO: try moving object.
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(window);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}


