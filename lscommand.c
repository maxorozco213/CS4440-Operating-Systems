#include <stdio.h>
    main()
	{
		execl("/bin/ls", "ls", "-l", 0);
		printf("Can only get here on error\n");
	}
