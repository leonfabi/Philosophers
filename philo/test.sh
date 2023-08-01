valgrind --tool=helgrind ./philo 1 800 200 200 | grep "ERROR SUMMARY"
valgrind --tool=drd ./philo 1 800 200 200 | grep "ERROR SUMMARY"
valgrind --leak-check=full ./philo 1 800 200 200 | grep "ERROR SUMMARY"

valgrind --tool=helgrind ./philo 5 800 200 200 | grep "ERROR SUMMARY"
valgrind --tool=drd ./philo 5 800 200 200 | grep "ERROR SUMMARY"
valgrind --leak-check=full ./philo 5 800 200 200 | grep "ERROR SUMMARY"

valgrind --tool=helgrind ./philo 5 800 200 200 7 | grep "ERROR SUMMARY"
valgrind --tool=drd ./philo 5 800 200 200 7 | grep "ERROR SUMMARY"
valgrind --leak-check=full ./philo 5 800 200 200 7 | grep "ERROR SUMMARY"

valgrind --tool=helgrind ./philo 4 410 200 200 | grep "ERROR SUMMARY"
valgrind --tool=drd ./philo 4 410 200 200 | grep "ERROR SUMMARY"
valgrind --leak-check=full ./philo 4 410 200 200 | grep "ERROR SUMMARY"

valgrind --tool=helgrind ./philo 4 310 200 100 | grep "ERROR SUMMARY"
valgrind --tool=drd ./philo 4 310 200 100 | grep "ERROR SUMMARY"
valgrind --leak-check=full ./philo 4 310 200 100 | grep "ERROR SUMMARY"
