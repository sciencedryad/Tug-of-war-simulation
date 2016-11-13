#ifndef DEBUG
	#define ASSERT(x)
#else
	#define ASSERT(x) \
		if (! (x)) \
    {\
			cout << "ERROR! Assert ( "<< #x << " ) failed\n";\
			cout << "       on line " << __LINE__ ;\
			cout << " in file " << __FILE__<< "\n";\
      exit(8);\
    } 
#endif

#define ASSERTperm(x) \
	if (! (x)) \
  {\
		cout << "ERROR! Assert ( "<< #x << " ) failed\n";\
		cout << "       on line " << __LINE__ ;\
		cout << " in file " << __FILE__<< "\n";\
    exit(8);\
  } 

