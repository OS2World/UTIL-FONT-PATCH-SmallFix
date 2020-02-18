// ------------------------------------------------------
// Name:        fixdisp.cpp
// Description: Display driver hacker
// Authors:     Jason R. Shannon & Daniel J. Neades
// Licence:     Public Domain.
// Support:     None.
// ------------------------------------------------------

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int
main(int _argc, char** _argv)
{
  char* originalDLL = "/os2/dll/old-ibms332.dll";
  char* modifiedDLL = "/os2/dll/new-ibms332.dll";

  if (_argc > 1)
    originalDLL = _argv[1];
  if (_argc > 2)
    modifiedDLL = _argv[2];

  printf("Modifying %s, saving to %s\n", originalDLL, modifiedDLL);

  FILE* in = fopen(originalDLL, "rb");
  if (in)
    {
      FILE* out = fopen(modifiedDLL, "wb");
      if (out)
	{
	  struct stat info;
	  if (stat(originalDLL, &info) != -1)
	    {
	      const size_t length = info.st_size;
	      char* buffer = new char[length];
	      if (buffer)
		{
		  if (fread(buffer, 1, length, in) == length)
		    {
		      int dpiFixed = 0, fontFixed = 0, fontFixed2 = 0, iconFixed = 0;
		      for (char* a = buffer; a < buffer + length - 8; a++)
			{
			  if (!dpiFixed &&
			      a[0] == 0x78 && a[1] == 0x00 && a[2] == 0x00 && a[3] == 0x00 && a[4] == 0xa3)
			    {
			      dpiFixed++;
			      a[0] = 0x60;
			      printf("dpi patched at 0x%08x...\n", a - buffer);
			      for (int x = -4; x < 8; x++)
				printf("%02x ", a[x]);
			      printf("\n");
			    }
			  if (!iconFixed &&
			      a[0] == 0x28 && a[1] == 0x00 && a[2] == 0x28 && a[3] == 0x00 &&
			      a[4] == 0x20 && a[5] == 0x00 && a[6] == 0x20 && a[7] == 0x00)
			    {
			      iconFixed++;
			      a[0] = 0x20;
			      a[2] = 0x20;
			      printf("Icons patched at 0x%08x...\n", a - buffer);
			    }
			  if (!fontFixed &&
			      a[0] == 0x65 && a[1] == 0x00 && a[2] == 0x00 && a[3] == 0x00)
			    {
			      fontFixed++;
			      a[0] = 0x64;
			      printf("1024x768 Fonts patched at 0x%08x...\n", a - buffer);
			    }
			  if (!fontFixed2 &&
			      a[0] == 0x66 && a[1] == 0x00 && a[2] == 0x00 && a[3] == 0x00)
			    {
			      fontFixed2++;
			      a[0] = 0x64;
			      printf("1280x1024 Fonts patched at 0x%08x...\n", a - buffer);
			    }
			}
		      if (!fontFixed)
			printf("WARNING: 1024x768 fonts were NOT patched\n");
		      if (!fontFixed2)
			printf("WARNING: 1280x1024 fonts were NOT patched\n");
		      if (!dpiFixed)
			printf("WARNING: DPI was not patched\n");
		      if (!iconFixed)
			printf("WARNING: 32x32 icons were NOT patched\n");

		      if (fwrite(buffer, 1, length, out) != length)
			perror("writing output file");
		      else
			printf("Output file %s written...\n", modifiedDLL);
		    }
		  else
		    perror("loading input file");
		  delete [] buffer;
		}
	      else
		fprintf(stderr, "Not enough memory!\n");
	    }
	  else
	    perror("statting input file");

	  fclose(out);
	}
      else
	perror("opening output file");
      fclose(in);
    }
  else
    perror("opening input file");

  return 0;
}
