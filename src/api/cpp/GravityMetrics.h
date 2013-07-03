/*
 * GravityMetrics.h
 *
 *  Created on: Feb 7, 2013
 *      Author: Chris Brundick
 */

#ifndef GRAVITYMETRICS_H_
#define GRAVITYMETRICS_H_

#include "Utility.h"
#include <map>
#include <string>
#include <vector>

namespace gravity
{

class GravityMetrics;

/**
 * Generic Metrics Data for the Gravity Infrastructure
 */
class GravityMetrics
{
private:
    typedef struct MetricsSample
    {
        int messageCount;
        int byteCount;
    } MetricsSample;
    
    std::map<std::string, MetricsSample> metrics;
    uint64_t startTime;
    uint64_t endTime;
public:
    /**
     * Default Constructor. Creates and empty GravityMetrics object
     */
    GRAVITY_API GravityMetrics();

    /**
     * Constructor. Creates a GravityMetrics object and populates it from 
     * and incoming message on the provided socket
     * \param socket zmq_socket on which is an incoming GravityMetrics obj
     */
    GRAVITY_API GravityMetrics(void* socket); 

    /**
     * Default Destructor
     */
    GRAVITY_API virtual ~GravityMetrics();

	
    /**
     * Increment the message count metric
     * \param dataProductID data product ID for which the message count is to be incremented
     * \param count amount by which to increment the message count
     */
    GRAVITY_API void incrementMessageCount(std::string dataProductID, int count);

    /**
     * Increment the byte count metric
     * \param dataProductID data product ID for which the byte count is to be incremented
     * \param count amount by which to increment the byte count
     */
    GRAVITY_API void incrementByteCount(std::string dataProductID, int count);

    /**
     * Reset the metrics. This will reset all counts to zero and set the startTime for each
     * sample to the current time but maintain list of data product IDs
     */
    GRAVITY_API void reset();

    /**
     * Clear the metrics. This will clear all metrics data and data product IDs.
     */
    GRAVITY_API void clear();

    /**
     * Remove the tracking of a specific data product id
     * \param dataProductID id of data product to remove from metrics
     */
    GRAVITY_API void remove(std::string dataProductID);

    /**
     * Method to return the message count for the given data product ID
     * \param dataProductID data product ID for which message count is returned
     * \return message count
     */
    GRAVITY_API int getMessageCount(std::string);
    
    /**
     * Method to return the byte count for the given data product ID
     * \param dataProductID data product ID for which byte count is returned
     * \return byte count
     */
    GRAVITY_API int getByteCount(std::string);
    
    /**
     * Method to return the sample period start time
     * \return sample period start time (microsecond epoch time)
     */
    GRAVITY_API uint64_t getStartTime();

    /**
     * Method to return the sample period end time
     * \return sample period end time (microsecond epoch time)
     */
    GRAVITY_API uint64_t getEndTime();

    /**
     * Method to indicate that the collection period is complete
     */
    GRAVITY_API void done();

    /**
     * Method to return the sample period in seconds
     * \return sample period sec
     */
    GRAVITY_API double getSamplePeriodSeconds();

    /**
     * Method to send this MetricsData object on zmq socket
     * \param zmq_socket over which to send this MetricsData object
     */
    GRAVITY_API void sendAsMessage(void* socket);

    /**
     * Method to populate this MetricsData object from zmq socket
     * \param zmq_socket from which to populate this MetricsData object
     */
    GRAVITY_API void populateFromMessage(void* socket); 

    /**
     * Method to get the list of data product ID for which this
     * MetricsData has metrics
     * \return std::vector<std::string> vector of data product IDs
     */
    GRAVITY_API std::vector<std::string> getDataProductIDs();
};

} /* namespace gravity */
#endif /* GRAVITYMETRICS_H_ */