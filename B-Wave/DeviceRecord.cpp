#include "stdafx.h"
#include "DeviceRecord.h"

BoxAPI::DeviceRecord::DeviceRecord(ZGuessedProduct prod)
	: _prod(prod)
{

}

BoxAPI::DeviceRecord::DeviceRecord(const DeviceRecord &rec)
	: _prod(rec._prod)
{

}

BoxAPI::DeviceRecord::~DeviceRecord()
{

}

int			BoxAPI::DeviceRecord::getScore() const
{
	return this->_prod->score;
}

const std::string	BoxAPI::DeviceRecord::getVendor() const
{
	return this->_prod->vendor;
}

const std::string	BoxAPI::DeviceRecord::getProduct() const
{
	return this->_prod->product;
}

const std::string	BoxAPI::DeviceRecord::getImageUrl() const
{
	return this->_prod->image_url;
}

const std::string	BoxAPI::DeviceRecord::getFileName() const
{
	return this->_prod->file_name;
}