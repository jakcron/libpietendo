#pragma once
#include <nn/hac/define/nacp.h>

namespace nn
{
namespace hac
{
	class ApplicationControlProperty
	{
	public:
		struct sTitle
		{
			nacp::Language language;
			std::string name;
			std::string publisher;

			void operator=(const sTitle& other)
			{
				language = other.language;
				name = other.name;
				publisher = other.publisher;
			}

			bool operator==(const sTitle& other) const
			{
				return (language == other.language) \
					&& (name == other.name) \
					&& (publisher == other.publisher);
			}

			bool operator!=(const sTitle& other) const
			{
				return !operator==(other);
			}
		};

		struct sRating
		{
			nacp::Organisation organisation;
			int8_t age;

			void operator=(const sRating& other)
			{
				organisation = other.organisation;
				age = other.age;
			}

			bool operator==(const sRating& other) const
			{
				return (organisation == other.organisation) \
					&& (age == other.age);
			}

			bool operator!=(const sRating& other) const
			{
				return !operator==(other);
			}
		};

		struct sStorageSize
		{
			int64_t size;
			int64_t journal_size;

			void operator=(const sStorageSize& other)
			{
				size = other.size;
				journal_size = other.journal_size;
			}

			bool operator==(const sStorageSize& other) const
			{
				return (size == other.size) \
					&& (journal_size == other.journal_size);
			}

			bool operator!=(const sStorageSize& other) const
			{
				return !operator==(other);
			}
		};

		struct sNeighborDetectionClientConfiguration
		{
			struct sGroupConfiguration
			{
				uint64_t group_id;
				std::array<byte_t, nacp::kNeighborDetectionGroupConfigurationKeyLength> key;

				sGroupConfiguration() :
					group_id(0)
				{
					memset(key.data(), 0, key.size());
				}

				sGroupConfiguration& operator=(const sGroupConfiguration& other)
				{
					group_id = other.group_id;
					memcpy(key.data(), other.key.data(), key.size());

					return *this;
				}

				bool operator==(const sGroupConfiguration& other) const
				{
					return group_id == other.group_id \
						&& memcmp(key.data(), other.key.data(), key.size()) == 0;
				}

				bool operator!=(const sGroupConfiguration& other) const
				{
					return !operator==(other);
				}

				bool isNull() const
				{
					sGroupConfiguration null_data = sGroupConfiguration();

					return *this == null_data;
				}
			};

			sGroupConfiguration send_data_configuration;
			sGroupConfiguration receivable_data_configuration[nacp::kReceivableGroupConfigurationCount];

			size_t countSendGroupConfig() const
			{
				return send_data_configuration.isNull() ? 0 : 1;
			}

			size_t countReceivableGroupConfig() const
			{
				size_t not_null_count = 0;

				for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
				{
					if (receivable_data_configuration[i].isNull() == false)
						not_null_count++;
				}

				return not_null_count;
			}

			sNeighborDetectionClientConfiguration() :
				send_data_configuration(),
				receivable_data_configuration()
			{
			}

			sNeighborDetectionClientConfiguration& operator=(const sNeighborDetectionClientConfiguration& other)
			{
				send_data_configuration = other.send_data_configuration;
				for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
				{
					receivable_data_configuration[i] = other.receivable_data_configuration[i];
				}

				return *this;
			}

			bool operator==(const sNeighborDetectionClientConfiguration& other) const
			{
				size_t recv_data_match_count = 0;

				for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
				{
					if (receivable_data_configuration[i] == other.receivable_data_configuration[i])
						recv_data_match_count++;
				}

				return send_data_configuration == other.send_data_configuration \
					&& recv_data_match_count == nacp::kReceivableGroupConfigurationCount;
			}

			bool operator!=(const sNeighborDetectionClientConfiguration& other) const
			{
				return !operator==(other);
			}
		};

		struct sJitConfiguration
		{
			bool is_enabled;
			uint64_t memory_size;

			sJitConfiguration() :
				is_enabled(false),
				memory_size(0)
			{
			}

			sJitConfiguration& operator=(const sJitConfiguration& other)
			{
				is_enabled = other.is_enabled;
				memory_size = other.memory_size;

				return *this;
			}

			bool operator==(const sJitConfiguration& other) const
			{
				return is_enabled == other.is_enabled \
					&& memory_size == other.memory_size;
			}

			bool operator!=(const sJitConfiguration& other) const
			{
				return !operator==(other);
			}
		};

		ApplicationControlProperty();
		ApplicationControlProperty(const ApplicationControlProperty& other);

		void operator=(const ApplicationControlProperty& other);
		bool operator==(const ApplicationControlProperty& other) const;
		bool operator!=(const ApplicationControlProperty& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		const std::vector<sTitle>& getTitle() const;
		void setTitle(const std::vector<sTitle>& title);

		const std::string& getIsbn() const;
		void setIsbn(const std::string& isbn);

		nacp::StartupUserAccount getStartupUserAccount() const;
		void setStartupUserAccount(nacp::StartupUserAccount var);

		nacp::UserAccountSwitchLock getUserAccountSwitchLock() const;
		void setUserAccountSwitchLock(nacp::UserAccountSwitchLock var);

		nacp::AddOnContentRegistrationType getAddOnContentRegistrationType() const;
		void setAddOnContentRegistrationType(nacp::AddOnContentRegistrationType var);

		const std::vector<nacp::AttributeFlag>& getAttribute() const;
		void setAttribute(const std::vector<nacp::AttributeFlag>& var);

		const std::vector<nacp::Language>& getSupportedLanguage() const;
		void setSupportedLanguage(const std::vector<nacp::Language>& var);

		const std::vector<nacp::ParentalControlFlag>& getParentalControl() const;
		void setParentalControl(const std::vector<nacp::ParentalControlFlag>& var);

		nacp::Screenshot getScreenshot() const;
		void setScreenshot(nacp::Screenshot var);

		nacp::VideoCapture getVideoCapture() const;
		void setVideoCapture(nacp::VideoCapture var);

		nacp::DataLossConfirmation getDataLossConfirmation() const;
		void setDataLossConfirmation(nacp::DataLossConfirmation var);

		nacp::PlayLogPolicy getPlayLogPolicy() const;
		void setPlayLogPolicy(nacp::PlayLogPolicy var);

		uint64_t getPresenceGroupId() const;
		void setPresenceGroupId(uint64_t var);

		const std::vector<sRating>& getRatingAge() const;
		void setRatingAge(const std::vector<sRating>& var);

		const std::string& getDisplayVersion() const;
		void setDisplayVersion(const std::string& var);

		uint64_t getAddOnContentBaseId() const;
		void setAddOnContentBaseId(uint64_t var);

		uint64_t getSaveDataOwnerId() const;
		void setSaveDataOwnerId(uint64_t var);

		const sStorageSize& getUserAccountSaveDataSize() const;
		void setUserAccountSaveDataSize(const sStorageSize& var);

		const sStorageSize& getDeviceSaveDataSize() const;
		void setDeviceSaveDataSize(const sStorageSize& var);

		int64_t getBcatDeliveryCacheStorageSize() const;
		void setBcatDeliveryCacheStorageSize(int64_t var);

		const std::string& getApplicationErrorCodeCategory() const;
		void setApplicationErrorCodeCategory(const std::string& var);

		const std::vector<uint64_t>& getLocalCommunicationId() const;
		void setLocalCommunicationId(const std::vector<uint64_t>& var);

		nacp::LogoType getLogoType() const;
		void setLogoType(nacp::LogoType var);

		nacp::LogoHandling getLogoHandling() const;
		void setLogoHandling(nacp::LogoHandling var);

		nacp::RuntimeAddOnContentInstall getRuntimeAddOnContentInstall() const;
		void setRuntimeAddOnContentInstall(nacp::RuntimeAddOnContentInstall var);

		nacp::RuntimeParameterDelivery getRuntimeParameterDelivery() const;
		void setRuntimeParameterDelivery(nacp::RuntimeParameterDelivery var);

		nacp::CrashReport getCrashReport() const;
		void setCrashReport(nacp::CrashReport var);

		nacp::Hdcp getHdcp() const;
		void setHdcp(nacp::Hdcp var);

		uint64_t getSeedForPsuedoDeviceId() const;
		void setSeedForPsuedoDeviceId(uint64_t var);

		const std::string& getBcatPassphase() const;
		void setBcatPassphase(const std::string& var);

		const std::vector<nacp::StartupUserAccountOptionFlag>& getStartupUserAccountOption() const;
		void setStartupUserAccountOption(const std::vector<nacp::StartupUserAccountOptionFlag>& var);

		const sStorageSize& getUserAccountSaveDataMax() const;
		void setUserAccountSaveDataMax(const sStorageSize& var);

		const sStorageSize& getDeviceSaveDataMax() const;
		void setDeviceSaveDataMax(const sStorageSize& var);

		int64_t getTemporaryStorageSize() const;
		void setTemporaryStorageSize(int64_t var);

		const sStorageSize& getCacheStorageSize() const;
		void setCacheStorageSize(const sStorageSize& var);

		int64_t getCacheStorageDataAndJournalSizeMax() const;
		void setCacheStorageDataAndJournalSizeMax(int64_t var);

		uint16_t getCacheStorageIndexMax() const;
		void setCacheStorageIndexMax(uint16_t var);

		const std::vector<uint64_t>& getPlayLogQueryableApplicationId() const;
		void setPlayLogQueryableApplicationId(const std::vector<uint64_t>& var);

		nacp::PlayLogQueryCapability getPlayLogQueryCapability() const;
		void setPlayLogQueryCapability(nacp::PlayLogQueryCapability var);

		const std::vector<nacp::RepairFlag>& getRepair() const;
		void setRepair(const std::vector<nacp::RepairFlag>& var);

		byte_t getProgramIndex() const;
		void setProgramIndex(byte_t var);

		const std::vector<nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& getRequiredNetworkServiceLicenseOnLaunch() const;
		void setRequiredNetworkServiceLicenseOnLaunch(const std::vector<nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& var);

		const sNeighborDetectionClientConfiguration& getNeighborDetectionClientConfiguration() const;
		void setNeighborDetectionClientConfiguration(const sNeighborDetectionClientConfiguration& var);

		const sJitConfiguration& getJitConfiguration() const;
		void setJitConfiguration(const sJitConfiguration& var);

		const nacp::PlayReportPermission& getPlayReportPermission() const;
		void setPlayReportPermission(const nacp::PlayReportPermission& var);

		const nacp::CrashScreenshotForProd& getCrashScreenshotForProd() const;
		void setCrashScreenshotForProd(const nacp::CrashScreenshotForProd& var);

		const nacp::CrashScreenshotForDev& getCrashScreenshotForDev() const;
		void setCrashScreenshotForDev(const nacp::CrashScreenshotForDev& var);

		const std::vector<uint64_t>& getAccessibleLaunchRequiredVersionApplicationId() const;
		void setAccessibleLaunchRequiredVersionApplicationId(const std::vector<uint64_t>& var);

	private:
		const std::string kModuleName = "APPLICATION_CONTROL_PROPERTY";

		// raw data
		tc::ByteData mRawBinary;

		// variables
		std::vector<sTitle> mTitle;
		std::string mIsbn;
		nacp::StartupUserAccount mStartupUserAccount;
		nacp::UserAccountSwitchLock mUserAccountSwitchLock;
		nacp::AddOnContentRegistrationType mAddOnContentRegistrationType;
		std::vector<nacp::AttributeFlag> mAttribute;
		std::vector<nn::hac::nacp::Language> mSupportedLanguage;
		std::vector<nacp::ParentalControlFlag> mParentalControl;
		nacp::Screenshot mScreenshot;
		nacp::VideoCapture mVideoCapture;
		nacp::DataLossConfirmation mDataLossConfirmation;
		nacp::PlayLogPolicy mPlayLogPolicy;
		uint64_t mPresenceGroupId;
		std::vector<sRating> mRatingAge;
		std::string mDisplayVersion;
		uint64_t mAddOnContentBaseId;
		uint64_t mSaveDataOwnerId;
		sStorageSize mUserAccountSaveDataSize;
		sStorageSize mDeviceSaveDataSize;
		int64_t mBcatDeliveryCacheStorageSize;
		std::string mApplicationErrorCodeCategory;
		std::vector<uint64_t> mLocalCommunicationId;
		nacp::LogoType mLogoType;
		nacp::LogoHandling mLogoHandling;
		nacp::RuntimeAddOnContentInstall mRuntimeAddOnContentInstall;
		nacp::RuntimeParameterDelivery mRuntimeParameterDelivery;
		nacp::CrashReport mCrashReport;
		nacp::Hdcp mHdcp;
		uint64_t mSeedForPsuedoDeviceId;
		std::string mBcatPassphase;
		std::vector<nacp::StartupUserAccountOptionFlag> mStartupUserAccountOption;
		sStorageSize mUserAccountSaveDataMax;
		sStorageSize mDeviceSaveDataMax;
		int64_t mTemporaryStorageSize;
		sStorageSize mCacheStorageSize;
		int64_t mCacheStorageDataAndJournalSizeMax;
		uint16_t mCacheStorageIndexMax;
		std::vector<uint64_t> mPlayLogQueryableApplicationId;
		nacp::PlayLogQueryCapability mPlayLogQueryCapability;
		std::vector<nacp::RepairFlag> mRepair;
		byte_t mProgramIndex;
		std::vector<nacp::RequiredNetworkServiceLicenseOnLaunchFlag> mRequiredNetworkServiceLicenseOnLaunch;
		sNeighborDetectionClientConfiguration mNeighborDetectionClientConfiguration;
		sJitConfiguration mJitConfiguration;
		nacp::PlayReportPermission mPlayReportPermission;
		nacp::CrashScreenshotForProd mCrashScreenshotForProd;
		nacp::CrashScreenshotForDev mCrashScreenshotForDev;
		std::vector<uint64_t> mAccessibleLaunchRequiredVersionApplicationId;

		void serialiseGroupConfig(const sNeighborDetectionClientConfiguration::sGroupConfiguration& logical, sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised);
		void parseGroupConfig(const sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised, sNeighborDetectionClientConfiguration::sGroupConfiguration& logical);
	};
}
}