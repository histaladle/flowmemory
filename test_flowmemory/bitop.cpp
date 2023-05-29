void midbit(char *src,char *dst,int start_bit,int last_bit)
{
    int start_ch=start_bit/8;
    int end_ch=last_bit/8;
    int ch_len=end_ch-start_ch+1;
    int bit_ofs=start_bit%8;
    char neg_mask;
    int i=0;
    if(start_bit>last_bit)
	{
		return;
	}
    for(i=0;i<ch_len;i++)
	{
		if(i>0)
		{
			dst[i-1]|=(src[i]<<(8-bit_ofs));
		}

		dst[i]=src[i+start_ch]>>bit_ofs;
		if((src[i+start_ch]&0x80) && (bit_ofs>1))
		{
#ifdef __cplusplus
            neg_mask=char(0x80);
#else
            neg_mask=(char)0x80;
#endif
			neg_mask>>=(bit_ofs-1);
			dst[i]&=(~neg_mask);
		}
	}
}

void movebit(char *src,int src_bit_ofs,char *dst,int dst_bit_ofs,int bit_width)
{
    int s_ch_idx,d_ch_idx,s_bit_ofs,d_bit_ofs;
    int i=0;
	if(bit_width<0)
	{
		return;
	}
    for(i=0;i<bit_width;i++)
	{
		s_ch_idx=(src_bit_ofs+i)/8;
		d_ch_idx=(dst_bit_ofs+i)/8;

		s_bit_ofs=(src_bit_ofs+i)%8;
		d_bit_ofs=(dst_bit_ofs+i)%8;

		if((src[s_ch_idx]>>s_bit_ofs)&0x01)
		{
			dst[d_ch_idx]|=(1<<d_bit_ofs);
		}
		else
		{
			dst[d_ch_idx]&=~(1<<d_bit_ofs);
		}
	}
}

void swap_bit(char *data1,int bit1,char *data2,int bit2)
{
	int ch_idx1=bit1/8;
	int bit_ofs1=bit1%8;
	int ch_idx2=bit2/8;
	int bit_ofs2=bit2%8;

	char ch1=data1[ch_idx1];
	char ch2=data2[ch_idx2];

	data2[ch_idx2]&=~(1<<bit_ofs2);
	data2[ch_idx2]|=((ch1>>bit_ofs1)&0x01)<<bit_ofs2;

	data1[ch_idx1]&=~(1<<bit_ofs1);
	data1[ch_idx1]|=((ch2>>bit_ofs2)&0x01)<<bit_ofs1;
}

void reverse_bit_order(char *data,int start_bit,int last_bit)
{
    int bit_len=last_bit-start_bit+1;
    int center_bit=(start_bit+last_bit)/2;
    int i=0;
    if(start_bit>last_bit)
	{
		return;
	}
    for(i=0;i<bit_len/2;i++)
	{
		swap_bit(data,center_bit-i,data,center_bit+i+(bit_len+1)%2);
	}
}

void reverse_byte_order(char *data,int start_byte,int last_byte)
{
    int byte_len=last_byte-start_byte+1;
    int center_byte=(start_byte+last_byte)/2;
    char ch;
    int i=0;
    if(start_byte>last_byte)
	{
		return;
	}
    for(i=0;i<byte_len/2;i++)
	{
		ch=data[center_byte-i];
		data[center_byte-i]=data[center_byte+i+(byte_len+1)%2];
		data[center_byte+i+(byte_len+1)%2]=ch;
	}
}

void movebyte(char *data,int start_byte,int last_byte,int offset)
{
    int i=0;
    if(start_byte>last_byte)
    {
        return;
    }
    if(offset>0)
    {
        for(i=last_byte;i>=start_byte;i--)
        {
            data[i+offset]=data[i];
        }
    }
    else {
        for(i=start_byte;i<=last_byte;i++)
        {
            data[i+offset]=data[i];
        }
    }
}
