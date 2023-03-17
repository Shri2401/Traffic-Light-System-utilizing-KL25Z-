#ifndef LOG_H_
#define LOG_H_

#ifdef DEBUG

#define LOG PRINTF

#else

#define LOG(...)

#endif

#endif /* LOG_H_ */
