#ifndef __LUZ__
#define __LUZ__

class Luz {

	public:
		virtual void aplica() = 0;
		virtual void prep() = 0;
		virtual ~Luz() = default;
};

#endif
