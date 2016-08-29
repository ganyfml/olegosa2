// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan/bam_io.h>
#include <seqan_api/CharString.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>
#include <seqan_api/SeqString_conv.hpp>
#include <seqan_api/CharString_conv.hpp>

void cal_cigar(const SeqString& query_original, seqan::String<seqan::CigarElement<> >& cigar, unsigned long query_hit_SAIndex, int query_hit_length, const SeqSuffixArray& refSA)
{
	seqan::Gaps<seqan::Dna5String, seqan::ArrayGaps> query_gap;
	assignSource(query_gap, *conv_back(query_original));

	seqan::Infix<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> > &>::Type query_hit_seq = infixWithLength(indexText(*conv_back(refSA)), saAt(query_hit_SAIndex, *conv_back(refSA)), query_hit_length);
	seqan::Gaps<seqan::Infix<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> > &>::Type, seqan::ArrayGaps> ref_gap;
	assignSource(ref_gap, query_hit_seq);

	globalAlignment(query_gap, ref_gap, seqan::Score<int, seqan::Simple>(2, -1, -2, -1)
			, seqan::AlignConfig<false, false, false, false>());

	std::cout << "ref seq: " << query_original << '\n' << query_hit_seq << std::endl;

	seqan::getCigarString(cigar, ref_gap, query_gap, query_hit_length);
}

class SAMWritter
{
	typedef seqan::BamHeaderRecord::TTag TTag;

	public:
	SAMWritter(std::string path) :
		samFileOut(path.c_str())
		, header(seqan::BamHeader())
	{
		seqan::BamHeaderRecord first_record;
		first_record.type = seqan::BAM_HEADER_FIRST;
		appendValue(first_record.tags, TTag("VN", "1.4"));
		appendValue(first_record.tags, TTag("SO", "unsorted"));
		appendValue(header, first_record);
	}

	SAMWritter():
		samFileOut(std::cout, seqan::Sam())
		, header(seqan::BamHeader())
	{
		seqan::BamHeaderRecord first_record;
		first_record.type = seqan::BAM_HEADER_FIRST;
		appendValue(first_record.tags, TTag("VN", "1.4"));
		appendValue(first_record.tags, TTag("SO", "unsorted"));
		appendValue(header, first_record);
	}

	void append_header_ref_info(CharString ref_name, long ref_length)
	{
		seqan::BamHeaderRecord ref_record;
		ref_record.type = seqan::BAM_HEADER_REFERENCE;
		appendValue(ref_record.tags, TTag(
					"SN" 
					, *static_cast<const seqan::CharString*>(const_cast<void*>(ref_name.get_pointer()))));
		appendValue(ref_record.tags, TTag("LN", std::to_string(ref_length)));
		appendValue(header, ref_record);
	}

	void write_header()
	{
		writeHeader(samFileOut, header);
	}

	void write_record_with_no_hit(const SeqString& query_original, const CharString& seq_name, const CharString& query_qual)
	{
		seqan::BamAlignmentRecord record;
		record.flag = 4;
		record.qName = *conv_back(seq_name);
		record.seq = *conv_back(query_original);
		record.qual = *conv_back(query_qual);

		seqan::BamTagsDict tagsDict(record.tags);
		seqan::setTagValue(tagsDict, "NM", 2);
		writeRecord(samFileOut, record);
	}

	void write_record(const SeqString& query_original, unsigned long query_hit_SAIndex, int query_hit_length, const SeqSuffixArray& refSA, const CharString& seq_name, const CharString& query_qual)
	{
		seqan::BamAlignmentRecord record;
		record.flag = 4;
		record.qName = *conv_back(seq_name);
		record.seq = *conv_back(query_original);
		record.qual = *conv_back(query_qual);
		record.beginPos = refSA.SAIndex2SeqPos(query_hit_SAIndex);

		seqan::BamTagsDict tagsDict(record.tags);
		seqan::setTagValue(tagsDict, "NM", 2);

		//Write Cigar to SAM
		seqan::String<seqan::CigarElement<> > cigar;
		cal_cigar(query_original, cigar, query_hit_SAIndex, query_hit_length, refSA);
		record.cigar = cigar;	
		writeRecord(samFileOut, record);
	}

	private:
	seqan::BamFileOut samFileOut;
	seqan::BamHeader header;
};
