#ifndef CFMAP_CURNCY_POLCARD_REC_TYPES
#define CFMAP_CURNCY_POLCARD_REC_TYPES

#pragma pack(push)
#pragma pack(1)
class Curncy_polcard_rec : public RecordTemplate<Curncy_polcard_rec>
{
public:
	Variant
	{
		Case
		{
			StringField<35> whole_rec;
		};
		Case
		{
			Group
			{
				StringField<4> bank_id;
				StringField<4> source_curr;
				StringField<4> dest_curr;
				StringField<11> spot_rate;
				StringField<2> exponent;
				StringField<9> date;
				StringField<1> system;
			} curr_record;
		};
	};
};
#pragma pack(pop)

#endif // CFMAP_CURNCY_POLCARD_REC_TYPES
