#pragma once


#include <stdint.h>


class soft_init_param
{
    soft_init_param() {};
    ~soft_init_param() {};
};


class Accel_Payload
{
    public:        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			constructor for remote device payload
         *      \return         returns pointer to Accelerator payload objects
         */
        // ---------------------------------------------------------------------------------------------------------------------------------------------- 
        Accel_Payload() { }
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			destructor for remote device payload
         */
        // ---------------------------------------------------------------------------------------------------------------------------------------------- 
        virtual ~Accel_Payload() { }
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			serializes payload to sent ot remote device
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------       
        virtual void serialize() = 0;


        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			deserializes payload from remote device
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual void deserialize() = 0;

        
        void*       m_buffer;       /*!< pointer to payload on host device >*/
        uint64_t    m_remAddress;   /*!< address for payload on remote device >*/
        uint64_t    m_size;         /*!< size of payload >*/
};


class FPGA_hndl
{
    public:
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			initializes remote hardware for processing
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int hardware_init() = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			initializes software shim on host device for processing
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int software_init(soft_init_param* param) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			allocates host and remote memory space for remote device payload
         *		\param[in]	    pyld object holding metadata of payload
         *		\param[in]	    size size of payload
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------        
        virtual uint64_t allocate(Accel_Payload* pyld, uint64_t size) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			deallocates host and remote memory space for remote device payload
         *		\param[in]	    pyld object holding metadata of payload
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual void deallocate(Accel_Payload* pyld) = 0;

        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			remote rountine used to wait for remote device configuration (Simulation Only)
         *		\return			address to payload on success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual uint64_t waitConfig() = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			writes remote device configuration data to remote device
         *		\param[in]	    pyld object holding metadata of payload
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int wrConfig(Accel_Payload* pyld) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			reads remote device configuration data from remote device
         *		\param[in]	    pyld object holding metadata of payload
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int rdConfig(Accel_Payload* pyld) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			remote rountine used to wait for remote device paramater data (Simulation Only)
         *      \param[in,out]  addr address to place payload information
         *      \param[in]      size size of payload
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual void waitParam(uint64_t& addr, int& size) = 0;
       

        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			writes payload holding remote device paramater data to remote device
         *		\param[in]	    pyld object holding metadata of payload
         *      \return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int wrParam(Accel_Payload* pyld) = 0;
	
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			remote rountine used to wait for host signal for remote device to start processing (Simulation Only)
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int waitStart() = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			routine for host devie to signal remote device to start processing
         *		\param[in]	    pyld object holding information to start remote device
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int sendStart(Accel_Payload* pyld) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			routine used by host device to wait for signal from remote device that processing is complete
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int waitComplete() = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			routine used by remote device signal host device that processing is complete (Simulation Only)
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int sendComplete() = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			routine used by host device to receive output data from host device
         *		\param[in,out]	pyld object holding information to hold remote device output
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int getOutput(Accel_Payload* pyld) = 0;
        
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			routine used by remote device to send output data to host device (Simulation Only)
         *		\param[in,out]	pyld object holding information to hold remote device output
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int sendOutput(Accel_Payload* pyld) = 0;
        
        
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        /**
         *		\brief			host routine for reseting remote memory address space distribution
         *		\return			0 success, 1 failure
         */
        // ----------------------------------------------------------------------------------------------------------------------------------------------
        virtual int resetMemSpace() = 0;
        
        
        uint64_t m_remAddrOfst; /*!< holds next free address in remote memory. */ 
        uint64_t m_memStartOft; /*!< remote memory address start offset. */ 
};

