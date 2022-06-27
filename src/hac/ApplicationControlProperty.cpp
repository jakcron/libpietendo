#include <cstring>
#include <nn/hac/ApplicationControlProperty.h>

nn::hac::ApplicationControlProperty::ApplicationControlProperty()
{
	clear();
}

nn::hac::ApplicationControlProperty::ApplicationControlProperty(const ApplicationControlProperty& other)
{
	*this = other;
}

void nn::hac::ApplicationControlProperty::operator=(const ApplicationControlProperty& other)
{
	clear();
	mTitle = other.mTitle;
	mIsbn = other.mIsbn;
	mStartupUserAccount = other.mStartupUserAccount;
	mUserAccountSwitchLock = other.mUserAccountSwitchLock;
	mAddOnContentRegistrationType = other.mAddOnContentRegistrationType;
	mAttribute = other.mAttribute;
	mSupportedLanguage = other.mSupportedLanguage;
	mParentalControl = other.mParentalControl;
	mScreenshot = other.mScreenshot;
	mVideoCapture = other.mVideoCapture;
	mDataLossConfirmation = other.mDataLossConfirmation;
	mPlayLogPolicy = other.mPlayLogPolicy;
	mPresenceGroupId = other.mPresenceGroupId;
	mRatingAge = other.mRatingAge;
	mDisplayVersion = other.mDisplayVersion;
	mAddOnContentBaseId = other.mAddOnContentBaseId;
	mSaveDataOwnerId = other.mSaveDataOwnerId;
	mUserAccountSaveDataSize = other.mUserAccountSaveDataSize;
	mDeviceSaveDataSize = other.mDeviceSaveDataSize;
	mBcatDeliveryCacheStorageSize = other.mBcatDeliveryCacheStorageSize;
	mApplicationErrorCodeCategory = other.mApplicationErrorCodeCategory;
	mLocalCommunicationId = other.mLocalCommunicationId;
	mLogoType = other.mLogoType;
	mLogoHandling = other.mLogoHandling;
	mRuntimeAddOnContentInstall = other.mRuntimeAddOnContentInstall;
	mRuntimeParameterDelivery = other.mRuntimeParameterDelivery;
	mCrashReport = other.mCrashReport;
	mHdcp = other.mHdcp;
	mSeedForPsuedoDeviceId = other.mSeedForPsuedoDeviceId;
	mBcatPassphase = other.mBcatPassphase;
	mStartupUserAccountOption = other.mStartupUserAccountOption;
	mUserAccountSaveDataMax = other.mUserAccountSaveDataMax;
	mDeviceSaveDataMax = other.mDeviceSaveDataMax;
	mTemporaryStorageSize = other.mTemporaryStorageSize;
	mCacheStorageSize = other.mCacheStorageSize;
	mCacheStorageDataAndJournalSizeMax = other.mCacheStorageDataAndJournalSizeMax;
	mCacheStorageIndexMax = other.mCacheStorageIndexMax;
	mPlayLogQueryableApplicationId = other.mPlayLogQueryableApplicationId;
	mPlayLogQueryCapability = other.mPlayLogQueryCapability;
	mRepair = other.mRepair;
	mProgramIndex = other.mProgramIndex;
	mRequiredNetworkServiceLicenseOnLaunch = other.mRequiredNetworkServiceLicenseOnLaunch;
	mNeighborDetectionClientConfiguration = other.mNeighborDetectionClientConfiguration;
	mJitConfiguration = other.mJitConfiguration;
	mPlayReportPermission = other.mPlayReportPermission;
	mCrashScreenshotForProd = other.mCrashScreenshotForProd;
	mCrashScreenshotForDev = other.mCrashScreenshotForDev;
	mAccessibleLaunchRequiredVersionApplicationId = other.mAccessibleLaunchRequiredVersionApplicationId;
}

bool nn::hac::ApplicationControlProperty::operator==(const ApplicationControlProperty& other) const
{
	return (mTitle == other.mTitle) \
		&& (mIsbn == other.mIsbn) \
		&& (mStartupUserAccount == other.mStartupUserAccount) \
		&& (mUserAccountSwitchLock == other.mUserAccountSwitchLock) \
		&& (mAddOnContentRegistrationType == other.mAddOnContentRegistrationType) \
		&& (mAttribute == other.mAttribute) \
		&& (mSupportedLanguage == other.mSupportedLanguage) \
		&& (mParentalControl == other.mParentalControl) \
		&& (mScreenshot == other.mScreenshot) \
		&& (mVideoCapture == other.mVideoCapture) \
		&& (mDataLossConfirmation == other.mDataLossConfirmation) \
		&& (mPlayLogPolicy == other.mPlayLogPolicy) \
		&& (mPresenceGroupId == other.mPresenceGroupId) \
		&& (mRatingAge == other.mRatingAge) \
		&& (mDisplayVersion == other.mDisplayVersion) \
		&& (mAddOnContentBaseId == other.mAddOnContentBaseId) \
		&& (mSaveDataOwnerId == other.mSaveDataOwnerId) \
		&& (mUserAccountSaveDataSize == other.mUserAccountSaveDataSize) \
		&& (mDeviceSaveDataSize == other.mDeviceSaveDataSize) \
		&& (mBcatDeliveryCacheStorageSize == other.mBcatDeliveryCacheStorageSize) \
		&& (mApplicationErrorCodeCategory == other.mApplicationErrorCodeCategory) \
		&& (mLocalCommunicationId == other.mLocalCommunicationId) \
		&& (mLogoType == other.mLogoType) \
		&& (mLogoHandling == other.mLogoHandling) \
		&& (mRuntimeAddOnContentInstall == other.mRuntimeAddOnContentInstall) \
		&& (mRuntimeParameterDelivery == other.mRuntimeParameterDelivery) \
		&& (mCrashReport == other.mCrashReport) \
		&& (mHdcp == other.mHdcp) \
		&& (mSeedForPsuedoDeviceId == other.mSeedForPsuedoDeviceId) \
		&& (mBcatPassphase == other.mBcatPassphase) \
		&& (mStartupUserAccountOption == other.mStartupUserAccountOption) \
		&& (mUserAccountSaveDataMax == other.mUserAccountSaveDataMax) \
		&& (mDeviceSaveDataMax == other.mDeviceSaveDataMax) \
		&& (mTemporaryStorageSize == other.mTemporaryStorageSize) \
		&& (mCacheStorageSize == other.mCacheStorageSize) \
		&& (mCacheStorageDataAndJournalSizeMax == other.mCacheStorageDataAndJournalSizeMax) \
		&& (mCacheStorageIndexMax == other.mCacheStorageIndexMax) \
		&& (mPlayLogQueryableApplicationId == other.mPlayLogQueryableApplicationId) \
		&& (mPlayLogQueryCapability == other.mPlayLogQueryCapability) \
		&& (mRepair == other.mRepair) \
		&& (mProgramIndex == other.mProgramIndex) \
		&& (mRequiredNetworkServiceLicenseOnLaunch == other.mRequiredNetworkServiceLicenseOnLaunch) \
		&& (mNeighborDetectionClientConfiguration == other.mNeighborDetectionClientConfiguration) \
		&& (mJitConfiguration == other.mJitConfiguration) \
		&& (mPlayReportPermission == other.mPlayReportPermission) \
		&& (mCrashScreenshotForProd == other.mCrashScreenshotForProd) \
		&& (mCrashScreenshotForDev == other.mCrashScreenshotForDev) \
		&& (mAccessibleLaunchRequiredVersionApplicationId == other.mAccessibleLaunchRequiredVersionApplicationId);
}

bool nn::hac::ApplicationControlProperty::operator!=(const ApplicationControlProperty& other) const
{
	return !(*this == other);
}

void nn::hac::ApplicationControlProperty::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(nn::hac::sApplicationControlProperty));

	sApplicationControlProperty* nacp = (sApplicationControlProperty*)mRawBinary.data();

	// strings
	for (size_t i = 0; i < mTitle.size(); i++)
	{
		nacp->title[(byte_t)mTitle[i].language].name.encode(mTitle[i].name);
		nacp->title[(byte_t)mTitle[i].language].publisher.encode(mTitle[i].publisher);
	}

	for (size_t i = 0; i < mSupportedLanguage.size(); i++)
	{
		nacp->supported_language_flag.set((size_t)mSupportedLanguage[i]);
	}

	nacp->isbn.encode(mIsbn);
	nacp->display_version.encode(mDisplayVersion);
	nacp->application_error_code_category.encode(mApplicationErrorCodeCategory);
	nacp->bcat_passphrase.encode(mBcatPassphase);
	
	// bitfields
	for (size_t i = 0; i < mAttribute.size(); i++)
	{
		nacp->attribute_flag.set((size_t)mSupportedLanguage[i]);
	}

	for (size_t i = 0; i < mParentalControl.size(); i++)
	{
		nacp->parental_control_flag.set((size_t)mParentalControl[i]);
	}

	for (size_t i = 0; i < mStartupUserAccountOption.size(); i++)
	{
		nacp->startup_user_account_option.test((size_t)mStartupUserAccountOption[i]);
	}

	for (size_t i = 0; i < mRepair.size(); i++)
	{
		nacp->repair_flag.set((size_t)mRepair[i]);
	}

	for (size_t i = 0; i < mRequiredNetworkServiceLicenseOnLaunch.size(); i++)
	{
		nacp->required_network_service_license_on_launch_flag.set((size_t)mRequiredNetworkServiceLicenseOnLaunch[i]);
	}

	// enum type casts
	nacp->startup_user_account = (byte_t)mStartupUserAccount;
	nacp->user_account_switch_lock = (byte_t)mUserAccountSwitchLock;
	nacp->add_on_content_registration_type = (byte_t)mAddOnContentRegistrationType;
	nacp->screenshot = (byte_t)mScreenshot;
	nacp->video_capture = (byte_t)mVideoCapture;
	nacp->data_loss_confirmation = (byte_t)mDataLossConfirmation;
	nacp->play_log_policy = (byte_t)mPlayLogPolicy;
	nacp->logo_type = (byte_t)mLogoType;
	nacp->logo_handling = (byte_t)mLogoHandling;
	nacp->runtime_add_on_content_install = (byte_t)mRuntimeAddOnContentInstall;
	nacp->runtime_parameter_delivery = (byte_t)mRuntimeParameterDelivery;
	nacp->crash_report = (byte_t)mCrashReport;
	nacp->hdcp = (byte_t)mHdcp;
	nacp->play_log_query_capability = (byte_t)mPlayLogQueryCapability;
	nacp->play_report_permission = (byte_t)mPlayReportPermission;
	nacp->crash_screenshot_for_prod = (byte_t)mCrashScreenshotForProd;
	nacp->crash_screenshot_for_dev = (byte_t)mCrashScreenshotForDev;
	
	// misc params
	nacp->presence_group_id.wrap(mPresenceGroupId);
	memset(nacp->rating_age.data(), nacp::kUnusedAgeRating, nacp::kRatingAgeCount); // clear ratings
	for (size_t i = 0; i < mRatingAge.size(); i++)
	{
		nacp->rating_age[(byte_t)mRatingAge[i].organisation] = mRatingAge[i].age;
	}
	nacp->add_on_content_base_id.wrap(mAddOnContentBaseId);
	nacp->save_data_owner_id.wrap(mSaveDataOwnerId);
	for (size_t i = 0; i < mLocalCommunicationId.size() && i < nacp::kLocalCommunicationIdCount; i++)
	{
		nacp->local_communication_id[i].wrap(mLocalCommunicationId[i]);
	}
	nacp->seed_for_pseudo_device_id.wrap(mSeedForPsuedoDeviceId);
	for (size_t i = 0; i < mPlayLogQueryableApplicationId.size() && i < nacp::kPlayLogQueryableApplicationIdCount; i++)
	{
		nacp->play_log_queryable_application_id[i].wrap(mPlayLogQueryableApplicationId[i]);
	}
	nacp->cache_storage_index_max.wrap(mCacheStorageIndexMax);
	nacp->program_index = mProgramIndex;
	for (size_t i = 0; i < mAccessibleLaunchRequiredVersionApplicationId.size() && i < nacp::kMaxAccessibleLaunchRequiredVersionApplicationIdCount; i++)
	{
		nacp->accessible_launch_required_verison.application_id[i].wrap(mAccessibleLaunchRequiredVersionApplicationId[i]);
	}

	// sizes
	nacp->user_account_save_data_size.wrap(mUserAccountSaveDataSize.size);
	nacp->user_account_save_data_journal_size.wrap(mUserAccountSaveDataSize.journal_size);
	nacp->device_save_data_size.wrap(mDeviceSaveDataSize.size);
	nacp->device_save_data_journal_size.wrap(mDeviceSaveDataSize.journal_size);
	nacp->bcat_delivery_cache_storage_size.wrap(mBcatDeliveryCacheStorageSize);
	nacp->user_account_save_data_size_max.wrap(mUserAccountSaveDataMax.size);
	nacp->user_account_save_data_journal_size_max.wrap(mUserAccountSaveDataMax.journal_size);
	nacp->device_save_data_size_max.wrap(mDeviceSaveDataMax.size);
	nacp->device_save_data_journal_size_max.wrap(mDeviceSaveDataMax.journal_size);
	nacp->temporary_storage_size.wrap(mTemporaryStorageSize);
	nacp->cache_storage_size.wrap(mCacheStorageSize.size);
	nacp->cache_storage_journal_size.wrap(mCacheStorageSize.journal_size);
	nacp->cache_storage_data_and_journal_size_max.wrap(mCacheStorageDataAndJournalSizeMax);

	// jit configuration
	if (mJitConfiguration.is_enabled)
		nacp->jit_configuration.jit_configuration_flag.set((size_t)nacp::JitConfigurationFlag::Enabled);
	nacp->jit_configuration.memory_size.wrap(mJitConfiguration.memory_size);

	// neighbor detection client configuration
	serialiseGroupConfig(mNeighborDetectionClientConfiguration.send_data_configuration, nacp->neighbour_detection_client_configuration.send_group_configuration);
	for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
	{
		serialiseGroupConfig(mNeighborDetectionClientConfiguration.receivable_data_configuration[i], nacp->neighbour_detection_client_configuration.receivable_group_configuration[i]);
	}
}

void nn::hac::ApplicationControlProperty::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(nn::hac::sApplicationControlProperty))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NACP too small");
	}

	clear();

	mRawBinary = tc::ByteData(sizeof(nn::hac::sApplicationControlProperty));
	memcpy(mRawBinary.data(), bytes, mRawBinary.size());

	const sApplicationControlProperty* nacp = (const sApplicationControlProperty*)mRawBinary.data();

	// strings
	for (size_t i = 0; i < nacp::kMaxLanguageCount; i++)
	{
		if (nacp->supported_language_flag.test(i))
		{
			mSupportedLanguage.push_back(nacp::Language(i));
		}
		if (!nacp->title[i].name.decode().empty() && !nacp->title[i].publisher.decode().empty())
		{
			mTitle.push_back({ nacp::Language(i), nacp->title[i].name.decode(), nacp->title[i].publisher.decode() });
		}
	}

	mIsbn = nacp->isbn.decode();
	mDisplayVersion = nacp->display_version.decode();
	mApplicationErrorCodeCategory = nacp->application_error_code_category.decode();
	mBcatPassphase = nacp->bcat_passphrase.decode();

	// bitfield values
	for (size_t i = 0; i < nacp->attribute_flag.bit_size(); i++)
	{
		if (nacp->attribute_flag.test(i))
		{
			mAttribute.push_back(nacp::AttributeFlag(i));
		}
	}
	for (size_t i = 0; i < nacp->parental_control_flag.bit_size(); i++)
	{
		if (nacp->parental_control_flag.test(i))
		{
			mParentalControl.push_back(nacp::ParentalControlFlag(i));
		}
	}
	for (size_t i = 0; i < nacp->startup_user_account_option.bit_size(); i++)
	{
		if (nacp->startup_user_account_option.test(i))
		{
			mStartupUserAccountOption.push_back(nacp::StartupUserAccountOptionFlag(i));
		}
	}
	for (size_t i = 0; i < nacp->repair_flag.bit_size(); i++)
	{
		if (nacp->repair_flag.test(i))
		{
			mRepair.push_back(nacp::RepairFlag(i));
		}
	}

	for (size_t i = 0; i < nacp->required_network_service_license_on_launch_flag.bit_size(); i++)
	{
		if (nacp->required_network_service_license_on_launch_flag.test(i))
		{
			mRequiredNetworkServiceLicenseOnLaunch.push_back(nacp::RequiredNetworkServiceLicenseOnLaunchFlag(i));
		}
	}
	// enum type casts
	mStartupUserAccount = nacp::StartupUserAccount(nacp->startup_user_account);
	mUserAccountSwitchLock = nacp::UserAccountSwitchLock(nacp->user_account_switch_lock);
	mAddOnContentRegistrationType = nacp::AddOnContentRegistrationType(nacp->add_on_content_registration_type);
	mScreenshot = nacp::Screenshot(nacp->screenshot);
	mVideoCapture = nacp::VideoCapture(nacp->video_capture);
	mDataLossConfirmation = nacp::DataLossConfirmation(nacp->data_loss_confirmation);
	mPlayLogPolicy = nacp::PlayLogPolicy(nacp->play_log_policy);
	mLogoType = nacp::LogoType(nacp->logo_type);
	mLogoHandling = nacp::LogoHandling(nacp->logo_handling);
	mRuntimeAddOnContentInstall = nacp::RuntimeAddOnContentInstall(nacp->runtime_add_on_content_install);
	mRuntimeParameterDelivery = nacp::RuntimeParameterDelivery(nacp->runtime_parameter_delivery);
	mCrashReport = nacp::CrashReport(nacp->crash_report);
	mHdcp = nacp::Hdcp(nacp->hdcp);
	mPlayLogQueryCapability = nacp::PlayLogQueryCapability(nacp->play_log_query_capability);
	mPlayReportPermission = nacp::PlayReportPermission(nacp->play_report_permission);
	mCrashScreenshotForProd = nacp::CrashScreenshotForProd(nacp->crash_screenshot_for_prod);
	mCrashScreenshotForDev = nacp::CrashScreenshotForDev(nacp->crash_screenshot_for_dev);

	// misc params
	mPresenceGroupId = nacp->presence_group_id.unwrap();
	for (size_t i = 0; i < nacp::kRatingAgeCount; i++)
	{
		if (nacp->rating_age[i] != nacp::kUnusedAgeRating)
			mRatingAge.push_back({nacp::Organisation(i), nacp->rating_age[i]});
	}
	mAddOnContentBaseId = nacp->add_on_content_base_id.unwrap();
	mSaveDataOwnerId = nacp->save_data_owner_id.unwrap();
	for (size_t i = 0; i < nacp::kLocalCommunicationIdCount; i++)
	{
		if (nacp->local_communication_id[i].unwrap() != 0)
			mLocalCommunicationId.push_back(nacp->local_communication_id[i].unwrap());
	}
	mSeedForPsuedoDeviceId = nacp->seed_for_pseudo_device_id.unwrap();
	for (size_t i = 0; i < nacp::kPlayLogQueryableApplicationIdCount; i++)
	{
		if (nacp->play_log_queryable_application_id[i].unwrap() != 0)
			mPlayLogQueryableApplicationId.push_back(nacp->play_log_queryable_application_id[i].unwrap());
	}
	mCacheStorageIndexMax = nacp->cache_storage_index_max.unwrap();
	mProgramIndex = nacp->program_index;
	for (size_t i = 0; i < nacp::kMaxAccessibleLaunchRequiredVersionApplicationIdCount; i++)
	{
		if (nacp->accessible_launch_required_verison.application_id[i].unwrap() != 0)
			mAccessibleLaunchRequiredVersionApplicationId.push_back(nacp->accessible_launch_required_verison.application_id[i].unwrap());
	}

	// sizes
	mUserAccountSaveDataSize.size = (int64_t)nacp->user_account_save_data_size.unwrap();
	mUserAccountSaveDataSize.journal_size = (int64_t)nacp->user_account_save_data_journal_size.unwrap();
	mDeviceSaveDataSize.size = (int64_t)nacp->device_save_data_size.unwrap();
	mDeviceSaveDataSize.journal_size = (int64_t)nacp->device_save_data_journal_size.unwrap();
	mBcatDeliveryCacheStorageSize = (int64_t)nacp->bcat_delivery_cache_storage_size.unwrap();
	mUserAccountSaveDataMax.size = (int64_t)nacp->user_account_save_data_size_max.unwrap();
	mUserAccountSaveDataMax.journal_size = (int64_t)nacp->user_account_save_data_journal_size_max.unwrap();
	mDeviceSaveDataMax.size = (int64_t)nacp->device_save_data_size_max.unwrap();
	mDeviceSaveDataMax.journal_size = (int64_t)nacp->device_save_data_journal_size_max.unwrap();
	mTemporaryStorageSize = (int64_t)nacp->temporary_storage_size.unwrap();
	mCacheStorageSize.size = (int64_t)nacp->cache_storage_size.unwrap();
	mCacheStorageSize.journal_size = (int64_t)nacp->cache_storage_journal_size.unwrap();
	mCacheStorageDataAndJournalSizeMax = (int64_t)nacp->cache_storage_data_and_journal_size_max.unwrap();

	// jit configuration
	mJitConfiguration.is_enabled = nacp->jit_configuration.jit_configuration_flag.test((size_t)nacp::JitConfigurationFlag::Enabled);
	mJitConfiguration.memory_size = nacp->jit_configuration.memory_size.unwrap();

	// neighbor detection client configuration
	parseGroupConfig(nacp->neighbour_detection_client_configuration.send_group_configuration, mNeighborDetectionClientConfiguration.send_data_configuration);
	for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
	{
		parseGroupConfig(nacp->neighbour_detection_client_configuration.receivable_group_configuration[i], mNeighborDetectionClientConfiguration.receivable_data_configuration[i]);
	}
}

const tc::ByteData& nn::hac::ApplicationControlProperty::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ApplicationControlProperty::clear()
{
	mRawBinary = tc::ByteData();
	mTitle.clear();
	mIsbn.clear();
	mStartupUserAccount = nacp::StartupUserAccount::None;
	mUserAccountSwitchLock = nacp::UserAccountSwitchLock::Disable;
	mAddOnContentRegistrationType = nacp::AddOnContentRegistrationType::AllOnLaunch;
	mAttribute.clear();
	mSupportedLanguage.clear();
	mParentalControl.clear();
	mScreenshot = nacp::Screenshot::Allow;
	mVideoCapture = nacp::VideoCapture::Disable;
	mDataLossConfirmation = nacp::DataLossConfirmation::None;
	mPlayLogPolicy = nacp::PlayLogPolicy::All;
	mPresenceGroupId = 0;
	mRatingAge.clear();
	mDisplayVersion.clear();
	mAddOnContentBaseId = 0;
	mSaveDataOwnerId = 0;
	mUserAccountSaveDataSize = {0, 0};
	mDeviceSaveDataSize = {0, 0};
	mBcatDeliveryCacheStorageSize = 0;
	mApplicationErrorCodeCategory.clear();
	mLocalCommunicationId.clear();
	mLogoType = nacp::LogoType::Nintendo;
	mLogoHandling = nacp::LogoHandling::Auto;
	mRuntimeAddOnContentInstall = nacp::RuntimeAddOnContentInstall::Deny;
	mCrashReport = nacp::CrashReport::Deny;
	mHdcp = nacp::Hdcp::None;
	mSeedForPsuedoDeviceId = 0;
	mBcatPassphase.clear();
	mStartupUserAccountOption.clear();
	mUserAccountSaveDataMax = {0, 0};
	mDeviceSaveDataMax = {0, 0};
	mTemporaryStorageSize = 0;
	mCacheStorageSize = {0, 0};
	mCacheStorageDataAndJournalSizeMax = 0;
	mCacheStorageIndexMax = 0;
	mPlayLogQueryableApplicationId.clear();
	mPlayLogQueryCapability = nacp::PlayLogQueryCapability::None;
	mRepair.clear();
	mProgramIndex = 0;
	mRequiredNetworkServiceLicenseOnLaunch.clear();
	mNeighborDetectionClientConfiguration = sNeighborDetectionClientConfiguration();
	mJitConfiguration = sJitConfiguration();
	mPlayReportPermission = nacp::PlayReportPermission::None;
	mCrashScreenshotForProd = nacp::CrashScreenshotForProd::Deny;
	mCrashScreenshotForDev = nacp::CrashScreenshotForDev::Deny;
	mAccessibleLaunchRequiredVersionApplicationId.clear();
}

const std::vector<nn::hac::ApplicationControlProperty::sTitle>& nn::hac::ApplicationControlProperty::getTitle() const
{
	return mTitle;
}

void nn::hac::ApplicationControlProperty::setTitle(const std::vector<sTitle>& title)
{
	mTitle = title;
}

const std::string& nn::hac::ApplicationControlProperty::getIsbn() const
{
	return mIsbn;
}

void nn::hac::ApplicationControlProperty::setIsbn(const std::string& isbn)
{
	mIsbn = isbn;
}

nn::hac::nacp::StartupUserAccount nn::hac::ApplicationControlProperty::getStartupUserAccount() const
{
	return mStartupUserAccount;
}

void nn::hac::ApplicationControlProperty::setStartupUserAccount(nacp::StartupUserAccount var)
{
	mStartupUserAccount = var;
}

nn::hac::nacp::UserAccountSwitchLock nn::hac::ApplicationControlProperty::getUserAccountSwitchLock() const
{
	return mUserAccountSwitchLock;
}

void nn::hac::ApplicationControlProperty::setUserAccountSwitchLock(nacp::UserAccountSwitchLock var)
{
	mUserAccountSwitchLock = var;
}

nn::hac::nacp::AddOnContentRegistrationType nn::hac::ApplicationControlProperty::getAddOnContentRegistrationType() const
{
	return mAddOnContentRegistrationType;
}

void nn::hac::ApplicationControlProperty::setAddOnContentRegistrationType(nacp::AddOnContentRegistrationType var)
{
	mAddOnContentRegistrationType = var;
}

const std::vector<nn::hac::nacp::AttributeFlag>& nn::hac::ApplicationControlProperty::getAttribute() const
{
	return mAttribute;
}

void nn::hac::ApplicationControlProperty::setAttribute(const std::vector<nacp::AttributeFlag>& var)
{
	mAttribute = var;
}

const std::vector<nn::hac::nacp::Language>& nn::hac::ApplicationControlProperty::getSupportedLanguage() const
{
	return mSupportedLanguage;
}

void nn::hac::ApplicationControlProperty::setSupportedLanguage(const std::vector<nacp::Language>& var)
{
	mSupportedLanguage = var;
}

const std::vector<nn::hac::nacp::ParentalControlFlag>& nn::hac::ApplicationControlProperty::getParentalControl() const
{
	return mParentalControl;
}

void nn::hac::ApplicationControlProperty::setParentalControl(const std::vector<nacp::ParentalControlFlag>& var)
{
	mParentalControl = var;
}

nn::hac::nacp::Screenshot nn::hac::ApplicationControlProperty::getScreenshot() const
{
	return mScreenshot;
}

void nn::hac::ApplicationControlProperty::setScreenshot(nacp::Screenshot var)
{
	mScreenshot = var;
}

nn::hac::nacp::VideoCapture nn::hac::ApplicationControlProperty::getVideoCapture() const
{
	return mVideoCapture;
}

void nn::hac::ApplicationControlProperty::setVideoCapture(nacp::VideoCapture var)
{
	mVideoCapture = var;
}

nn::hac::nacp::DataLossConfirmation nn::hac::ApplicationControlProperty::getDataLossConfirmation() const
{
	return mDataLossConfirmation;
}

void nn::hac::ApplicationControlProperty::setDataLossConfirmation(nacp::DataLossConfirmation var)
{
	mDataLossConfirmation = var;
}

nn::hac::nacp::PlayLogPolicy nn::hac::ApplicationControlProperty::getPlayLogPolicy() const
{
	return mPlayLogPolicy;
}

void nn::hac::ApplicationControlProperty::setPlayLogPolicy(nacp::PlayLogPolicy var)
{
	mPlayLogPolicy = var;
}

uint64_t nn::hac::ApplicationControlProperty::getPresenceGroupId() const
{
	return mPresenceGroupId;
}

void nn::hac::ApplicationControlProperty::setPresenceGroupId(uint64_t var)
{
	mPresenceGroupId = var;
}

const std::vector<nn::hac::ApplicationControlProperty::sRating>& nn::hac::ApplicationControlProperty::getRatingAge() const
{
	return mRatingAge;
}

void nn::hac::ApplicationControlProperty::setRatingAge(const std::vector<sRating>& var)
{
	mRatingAge = var;
}

const std::string& nn::hac::ApplicationControlProperty::getDisplayVersion() const
{
	return mDisplayVersion;
}

void nn::hac::ApplicationControlProperty::setDisplayVersion(const std::string& var)
{
	mDisplayVersion = var;
}

uint64_t nn::hac::ApplicationControlProperty::getAddOnContentBaseId() const
{
	return mAddOnContentBaseId;
}

void nn::hac::ApplicationControlProperty::setAddOnContentBaseId(uint64_t var)
{
	mAddOnContentBaseId = var;
}

uint64_t nn::hac::ApplicationControlProperty::getSaveDataOwnerId() const
{
	return mSaveDataOwnerId;
}

void nn::hac::ApplicationControlProperty::setSaveDataOwnerId(uint64_t var)
{
	mSaveDataOwnerId = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getUserAccountSaveDataSize() const
{
	return mUserAccountSaveDataSize;
}

void nn::hac::ApplicationControlProperty::setUserAccountSaveDataSize(const sStorageSize& var)
{
	mUserAccountSaveDataSize = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getDeviceSaveDataSize() const
{
	return mDeviceSaveDataSize;
}

void nn::hac::ApplicationControlProperty::setDeviceSaveDataSize(const sStorageSize& var)
{
	mDeviceSaveDataSize = var;
}

int64_t nn::hac::ApplicationControlProperty::getBcatDeliveryCacheStorageSize() const
{
	return mBcatDeliveryCacheStorageSize;
}

void nn::hac::ApplicationControlProperty::setBcatDeliveryCacheStorageSize(int64_t var)
{
	mBcatDeliveryCacheStorageSize = var;
}

const std::string& nn::hac::ApplicationControlProperty::getApplicationErrorCodeCategory() const
{
	return mApplicationErrorCodeCategory;
}

void nn::hac::ApplicationControlProperty::setApplicationErrorCodeCategory(const std::string& var)
{
	mApplicationErrorCodeCategory = var;
}

const std::vector<uint64_t>& nn::hac::ApplicationControlProperty::getLocalCommunicationId() const
{
	return mLocalCommunicationId;
}

void nn::hac::ApplicationControlProperty::setLocalCommunicationId(const std::vector<uint64_t>& var)
{
	mLocalCommunicationId = var;
}

nn::hac::nacp::LogoType nn::hac::ApplicationControlProperty::getLogoType() const
{
	return mLogoType;
}

void nn::hac::ApplicationControlProperty::setLogoType(nacp::LogoType var)
{
	mLogoType = var;
}

nn::hac::nacp::LogoHandling nn::hac::ApplicationControlProperty::getLogoHandling() const
{
	return mLogoHandling;
}

void nn::hac::ApplicationControlProperty::setLogoHandling(nacp::LogoHandling var)
{
	mLogoHandling = var;
}

nn::hac::nacp::RuntimeAddOnContentInstall nn::hac::ApplicationControlProperty::getRuntimeAddOnContentInstall() const
{
	return mRuntimeAddOnContentInstall;
}

void nn::hac::ApplicationControlProperty::setRuntimeAddOnContentInstall(nacp::RuntimeAddOnContentInstall var)
{
	mRuntimeAddOnContentInstall = var;
}

nn::hac::nacp::RuntimeParameterDelivery nn::hac::ApplicationControlProperty::getRuntimeParameterDelivery() const
{
	return mRuntimeParameterDelivery;
}

void nn::hac::ApplicationControlProperty::setRuntimeParameterDelivery(nacp::RuntimeParameterDelivery var)
{
	mRuntimeParameterDelivery = var;
}

nn::hac::nacp::CrashReport nn::hac::ApplicationControlProperty::getCrashReport() const
{
	return mCrashReport;
}

void nn::hac::ApplicationControlProperty::setCrashReport(nacp::CrashReport var)
{
	mCrashReport = var;
}

nn::hac::nacp::Hdcp nn::hac::ApplicationControlProperty::getHdcp() const
{
	return mHdcp;
}

void nn::hac::ApplicationControlProperty::setHdcp(nacp::Hdcp var)
{
	mHdcp = var;
}

uint64_t nn::hac::ApplicationControlProperty::getSeedForPsuedoDeviceId() const
{
	return mSeedForPsuedoDeviceId;
}

void nn::hac::ApplicationControlProperty::setSeedForPsuedoDeviceId(uint64_t var)
{
	mSeedForPsuedoDeviceId = var;
}

const std::string& nn::hac::ApplicationControlProperty::getBcatPassphase() const
{
	return mBcatPassphase;
}

void nn::hac::ApplicationControlProperty::setBcatPassphase(const std::string& var)
{
	mBcatPassphase = var;
}

const std::vector<nn::hac::nacp::StartupUserAccountOptionFlag>& nn::hac::ApplicationControlProperty::getStartupUserAccountOption() const
{
	return mStartupUserAccountOption;
}

void nn::hac::ApplicationControlProperty::setStartupUserAccountOption(const std::vector<nacp::StartupUserAccountOptionFlag>& var)
{
	mStartupUserAccountOption = var;
}


const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getUserAccountSaveDataMax() const
{
	return mUserAccountSaveDataMax;
}

void nn::hac::ApplicationControlProperty::setUserAccountSaveDataMax(const sStorageSize& var)
{
	mUserAccountSaveDataMax = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getDeviceSaveDataMax() const
{
	return mDeviceSaveDataMax;
}

void nn::hac::ApplicationControlProperty::setDeviceSaveDataMax(const sStorageSize& var)
{
	mDeviceSaveDataMax = var;
}

int64_t nn::hac::ApplicationControlProperty::getTemporaryStorageSize() const
{
	return mTemporaryStorageSize;
}

void nn::hac::ApplicationControlProperty::setTemporaryStorageSize(int64_t var)
{
	mTemporaryStorageSize = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getCacheStorageSize() const
{
	return mCacheStorageSize;
}

void nn::hac::ApplicationControlProperty::setCacheStorageSize(const sStorageSize& var)
{
	mCacheStorageSize = var;
}

int64_t nn::hac::ApplicationControlProperty::getCacheStorageDataAndJournalSizeMax() const
{
	return mCacheStorageDataAndJournalSizeMax;
}

void nn::hac::ApplicationControlProperty::setCacheStorageDataAndJournalSizeMax(int64_t var)
{
	mCacheStorageDataAndJournalSizeMax = var;
}

uint16_t nn::hac::ApplicationControlProperty::getCacheStorageIndexMax() const
{
	return mCacheStorageIndexMax;
}

void nn::hac::ApplicationControlProperty::setCacheStorageIndexMax(uint16_t var)
{
	mCacheStorageIndexMax = var;
}

const std::vector<uint64_t>& nn::hac::ApplicationControlProperty::getPlayLogQueryableApplicationId() const
{
	return mPlayLogQueryableApplicationId;
}

void nn::hac::ApplicationControlProperty::setPlayLogQueryableApplicationId(const std::vector<uint64_t>& var)
{
	mPlayLogQueryableApplicationId = var;
}

nn::hac::nacp::PlayLogQueryCapability nn::hac::ApplicationControlProperty::getPlayLogQueryCapability() const
{
	return mPlayLogQueryCapability;
}

void nn::hac::ApplicationControlProperty::setPlayLogQueryCapability(nacp::PlayLogQueryCapability var)
{
	mPlayLogQueryCapability = var;
}

const std::vector<nn::hac::nacp::RepairFlag>& nn::hac::ApplicationControlProperty::getRepair() const
{
	return mRepair;
}

void nn::hac::ApplicationControlProperty::setRepair(const std::vector<nacp::RepairFlag>& var)
{
	mRepair = var;
}

byte_t nn::hac::ApplicationControlProperty::getProgramIndex() const
{
	return mProgramIndex;
}

void nn::hac::ApplicationControlProperty::setProgramIndex(byte_t var)
{
	mProgramIndex = var;
}

const std::vector<nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& nn::hac::ApplicationControlProperty::getRequiredNetworkServiceLicenseOnLaunch() const
{
	return mRequiredNetworkServiceLicenseOnLaunch;
}

void nn::hac::ApplicationControlProperty::setRequiredNetworkServiceLicenseOnLaunch(const std::vector<nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& var)
{
	mRequiredNetworkServiceLicenseOnLaunch = var;
}

const nn::hac::ApplicationControlProperty::sNeighborDetectionClientConfiguration& nn::hac::ApplicationControlProperty::getNeighborDetectionClientConfiguration() const
{
	return mNeighborDetectionClientConfiguration;
}

void nn::hac::ApplicationControlProperty::setNeighborDetectionClientConfiguration(const sNeighborDetectionClientConfiguration& var)
{
	mNeighborDetectionClientConfiguration = var;
}

const nn::hac::ApplicationControlProperty::sJitConfiguration& nn::hac::ApplicationControlProperty::getJitConfiguration() const
{
	return mJitConfiguration;
}

void nn::hac::ApplicationControlProperty::setJitConfiguration(const sJitConfiguration& var)
{
	mJitConfiguration = var;
}

const nn::hac::nacp::PlayReportPermission& nn::hac::ApplicationControlProperty::getPlayReportPermission() const
{
	return mPlayReportPermission;
}

void nn::hac::ApplicationControlProperty::setPlayReportPermission(const nacp::PlayReportPermission& var)
{
	mPlayReportPermission = var;
}

const nn::hac::nacp::CrashScreenshotForProd& nn::hac::ApplicationControlProperty::getCrashScreenshotForProd() const
{
	return mCrashScreenshotForProd;
}

void nn::hac::ApplicationControlProperty::setCrashScreenshotForProd(const nacp::CrashScreenshotForProd& var)
{
	mCrashScreenshotForProd = var;
}

const nn::hac::nacp::CrashScreenshotForDev& nn::hac::ApplicationControlProperty::getCrashScreenshotForDev() const
{
	return mCrashScreenshotForDev;
}

void nn::hac::ApplicationControlProperty::setCrashScreenshotForDev(const nacp::CrashScreenshotForDev& var)
{
	mCrashScreenshotForDev = var;
}

const std::vector<uint64_t>& nn::hac::ApplicationControlProperty::getAccessibleLaunchRequiredVersionApplicationId() const
{
	return mAccessibleLaunchRequiredVersionApplicationId;
}

void nn::hac::ApplicationControlProperty::setAccessibleLaunchRequiredVersionApplicationId(const std::vector<uint64_t>& var)
{
	mAccessibleLaunchRequiredVersionApplicationId = var;
}

void nn::hac::ApplicationControlProperty::serialiseGroupConfig(const sNeighborDetectionClientConfiguration::sGroupConfiguration& logical, sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised)
{
	if (logical.isNull())
	{
		memset(&serialised, 0, sizeof(sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration));
		return;
	}

	serialised.group_id.wrap(logical.group_id);
	memcpy(serialised.key.data(), logical.key.data(), serialised.key.size());
}

void nn::hac::ApplicationControlProperty::parseGroupConfig(const sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised, sNeighborDetectionClientConfiguration::sGroupConfiguration& logical)
{
	logical.group_id = serialised.group_id.unwrap();
	memcpy(logical.key.data(), serialised.key.data(), serialised.key.size());
}