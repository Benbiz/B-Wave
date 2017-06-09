#ifndef DEVICERECORD_H_
# define DEVICERECORD_H_

namespace BoxAPI
{
	class DeviceRecord
	{
	public:
		DeviceRecord(ZGuessedProduct);
		DeviceRecord(const DeviceRecord &rec);
		~DeviceRecord();
		
		int					getScore() const;
		const std::string	getVendor() const;
		const std::string	getProduct() const;
		const std::string	getImageUrl() const;
		const std::string	getFileName() const;

	private:
		ZGuessedProduct	_prod;
	};
}

#endif /* !DEVICERECORD_H_ */