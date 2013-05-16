#ifndef FPS_H
#define FPS_H


class FPS
{
	private:
		FPS();

	public:
		static void update(); // count the frames for 1 second and print the count and recount.

	private:
		static float startTime; // time counting started
		static int count; // count the frames

};

#endif // FPS_H
