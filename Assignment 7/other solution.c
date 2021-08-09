int print2505(FILE *out, const char *format, const uint8_t *data)
{
	int char_count = 0;
	int fcounter = 0;
	int datacounter = 0;
	while (*format)
	{
		if (*(format + fcounter) == '%')
		{
			if (*(format + fcounter + 1) == '%')
			{
				char_out(out, *format);
				char_count++;
				fcounter = fcounter + 4;
			}
			else if (*(format + fcounter + 2) == 'l')
			{
				int n = *(format + fcounter + 1);
				n = n % 48;
				if (n == 1 || n == 2 || n == 4 || n  == 8)
				{
					char_out(out, '0');
					char_out(out, 'x');
					for (int i = n; i >= 0; i--)
					{
						char_out(out, *(data + datacounter));
						char_count++;
						datacounter++;
					}
					fcounter = fcounter + 5;
				}
				else
				{
					return -1;
				}
			}
			else if (*(format+ fcounter + 2) == 'b')
			{
				int n = *(format + fcounter + 1);
				n = n % 48;
				if (n == 1 || n == 2 || n == 4 || n  == 8)
				{
					char_out(out, '0');
					char_out(out, 'x');
					for (int i = 0; i < n; i++)
					{
						char_out(out, *(data + datacounter));
						char_count++;
						datacounter++;
					}
					fcounter = fcounter + 5;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				fcounter++;
			}

		}		
		else
		{
			char_out(out, *(format + fcounter));
			char_count++;
			fcounter++;
		}
	}

	return char_count;
}

