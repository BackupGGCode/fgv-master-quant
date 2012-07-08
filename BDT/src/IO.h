#define	TAM_MAX 100					//tree max dimension
class IO {

public:
	IO();
	void exportShortRate2RStudio(double short_rate[TAM_MAX][TAM_MAX], int N);
	void exportBondPrice2RStudio(double short_rate[TAM_MAX][TAM_MAX], int N);
	virtual ~IO();
};

