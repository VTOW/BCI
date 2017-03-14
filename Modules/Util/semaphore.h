#ifndef BCI_SEMAPHORE_H_INCLUDED
#define BCI_SEMAPHORE_H_INCLUDED

/**
 * Locks or unlocks a semaphore
 * Define flag BCI_SEM_DEBUG to use param str to print when a semphore is locked
 *  or unlocked
 * Define flag BCI_SEM_DEBUG_FULL to use param str to print when a semaphore is
 * 	locked or unlocked. This flag also enables over- and under-lock checking
 * Define flg BCI_SEM_DEBUG_FULL_OFF to use param str as an ignored parameter.
 *  This flag has identical behaviour with no flag, but exists so you don't have
 *  to refactor your code if you used other flags
 * @param sem Semaphore to use
 * @param str String to print for debug
 */
#if defined(BCI_SEM_DEBUG)
  #define BCI_lockSem(sem, str) writeDebugStreamLine("BCI_lockSem: %s",str);semaphoreLock(sem, 10000);if(bDoesTaskOwnSemaphore(sem))
  #define BCI_unlockSem(sem, str) writeDebugStreamLine("BCI_unlockSem: %s",str);if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#elif defined(BCI_SEM_DEBUG_FULL)
  int bci_sem_debug_full_counter;
  #define BCI_lockSem(sem, str) bci_sem_debug_full_counter++;if(bci_sem_debug_full_counter != 1){writeDebugStreamLine("BCI_lockSem: overlock at %s", str);bci_sem_debug_full_counter--;}else{writeDebugStreamLine("BCI_lockSem: %s",str);}semaphoreLock(sem, 10000);if(bDoesTaskOwnSemaphore(sem))
  #define BCI_unlockSem(sem, str) bci_sem_debug_full_counter--;if(bci_sem_debug_full_counter != 0){writeDebugStreamLine("BCI_unlockSem: underlock at %s", str);bci_sem_debug_full_counter++;}else{writeDebugStreamLine("BCI_unlockSem: %s",str);}if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#elif defined(BCI_SEM_DEBUG_FULL_OFF)
  #define BCI_lockSem(sem, str) semaphoreLock(sem, 10000);if(bDoesTaskOwnSemaphore(sem))
  #define BCI_unlockSem(sem, str) if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#else
  #define BCI_lockSem(sem) semaphoreLock(sem, 10000);if(bDoesTaskOwnSemaphore(sem))
  #define BCI_unlockSem(sem) if(bDoesTaskOwnSemaphore(sem)){semaphoreUnlock(sem);}
#endif //BCI_SEM_DEBUG

#endif //BCI_SEMAPHORE_H_INCLUDED
